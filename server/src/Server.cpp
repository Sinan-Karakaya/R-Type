/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Server
*/

#include "Server.hpp"
#include "Config.hpp"

namespace RType::Server
{
    Server::Server()
    {
        m_startingTimestamp =
            std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
                .count();
        SERVER_LOG_INFO("Loading server...");
        try {
            SERVER_LOG_INFO("Loading config file...");
            m_config = std::make_unique<Config>("server.properties");

            SERVER_LOG_INFO("Loading runtime library...");
            m_libHandle = RType::Utils::Modules::LoadSharedLibrary("runtime");
            ASSERT(m_libHandle, "Failed to load runtime library")

            SERVER_LOG_INFO("Trying to get runtime entry point...");
            RType::Runtime::IRuntime *(*runtimeEntry)() =
                (RType::Runtime::IRuntime * (*)()) RType::Utils::Modules::GetFunction(m_libHandle, "RuntimeEntry");
            ASSERT(runtimeEntry, "Failed to get runtime entry point")
            SERVER_LOG_INFO("Runtime entry point loaded");

            SERVER_LOG_INFO("Initializing runtime...");
            m_runtime = std::unique_ptr<RType::Runtime::IRuntime>(runtimeEntry());
            m_runtime->Init();
            SERVER_LOG_INFO("Runtime initialized");
        } catch (std::exception &e) {
            throw std::runtime_error(e.what());
        }

        this->m_fileProject = m_config->getField("PROJECT_FILE");
        SERVER_LOG_INFO("Project file: {0}", this->m_fileProject);

        try {
            this->m_port = std::stoi(m_config->getField("PORT"));
        } catch (std::exception &e) {
            throw std::runtime_error("Invalid port");
        }
        if (this->m_port < 1024 || this->m_port > 65535)
            throw std::runtime_error("Invalid port range");
        m_udpServer = std::make_unique<RType::Network::UDPServer>(*m_ioContext, this->m_port);
    }

    Server::~Server()
    {
        SERVER_LOG_INFO("Bye...");
        m_runtime->Destroy();
        m_runtime.reset();
        ASSERT(RType::Utils::Modules::FreeSharedLibrary(m_libHandle), "Failed to free runtime library")
    }

    void Server::run()
    {
        constexpr int ticksPerSecond = 20;
        const auto tickDuration = std::chrono::milliseconds(1000 / ticksPerSecond);

        this->m_running = true;
        m_udpServer->startReceive(
            std::bind(&Server::networkHandler, this, std::placeholders::_1, std::placeholders::_2));
        m_ioContext.run();

        long currentTimestamp =
            std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
                .count();
        SERVER_LOG_INFO("Server is running - Start in {0}ms", (currentTimestamp - m_startingTimestamp));
        while (this->m_running) {
            m_runtime->Update();
            networkClientsTimeoutChecker();
            std::this_thread::sleep_for(tickDuration);
        }
    }

    void Server::networkHandler(RType::Network::Packet &packet, asio::ip::udp::endpoint &endpoint)
    {
        if (packet.getType() == RType::Network::PacketType::HELLOSERVER) {
            RType::Network::PacketHelloServer helloServerPacket =
                dynamic_cast<RType::Network::PacketHelloServer &>(packet);
            if (helloServerPacket.getVersion() != std::stof(RTYPE_VERSION)) {
                return;
            }

            if (m_clients.contains(endpoint))
                SERVER_LOG_INFO("[{0}:{1}] Already connected, resend PacketHelloClient", endpoint.address().to_string(),
                                endpoint.port());
            else {
                Client client = {m_runtime->AddEntity(), packet.getTimestamp()};
                m_clients.insert({endpoint, client});
                SERVER_LOG_INFO("[{0}:{1}] Connected", endpoint.address().to_string(), endpoint.port());
                RTYPE_LOG_INFO("ECS assigned id {0} to client", client.id);
            }
            m_udpServer->sendData(RType::Network::PacketHelloClient(), endpoint);
            return;
        } else if (!m_clients.contains(endpoint)) {
            return;
        }

        m_clients[endpoint].lastPing =
            std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
                .count();
        switch (packet.getType()) {
        case RType::Network::PacketType::BYESERVER:
            SERVER_LOG_INFO("[{0}:{1}] Disconnected", endpoint.address().to_string(), endpoint.port());
            networkClientDisconnect(endpoint);
            m_clients.erase(endpoint);
            break;
        case RType::Network::PacketType::PING:
            m_udpServer->sendData(RType::Network::PacketPing(), endpoint);
            break;
        case RType::Network::PacketType::ENTITYMOVE:
            networkEntityMoveHandler(packet, endpoint);
            break;
        case RType::Network::PacketType::IMATEAPOT:
            SERVER_LOG_INFO("[{0}:{1}] I'm a teapot. Dumb client...", endpoint.address().to_string(), endpoint.port());
            break;
        }
    }

    void Server::networkClientsTimeoutChecker()
    {
        long currentTimestamp =
            std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
                .count();
        for (auto it = m_clients.begin(); it != m_clients.end();) {
            if (currentTimestamp - it->second.lastPing > 5000) {
                SERVER_LOG_INFO("[{0}:{1}] Timeout", it->first.address().to_string(), it->first.port());
                asio::ip::udp::endpoint endpoint = it->first;
                networkClientDisconnect(endpoint);
                it = m_clients.erase(it);
            } else {
                ++it;
            }
        }
    }

    void Server::networkClientDisconnect(asio::ip::udp::endpoint &endpoint)
    {
        uint32_t id = m_clients[endpoint].id;

        try {
            m_runtime->GetRegistry().DestroyEntity(id);
        } catch (std::exception &e) {
            SERVER_LOG_WARN("Failed to destroy entity {0}: {1}", id, e.what());
        }
        RType::Network::PacketPlayerDie packet(id);
        networkSendAll(packet);
    }

    void Server::networkSendAll(RType::Network::Packet &packet)
    {
        for (auto &client : m_clients) {
            m_udpServer->sendData(packet, client.first);
        }
    }

    void Server::networkEntityMoveHandler(RType::Network::Packet &packet, asio::ip::udp::endpoint &endpoint)
    {
        RType::Network::PacketEntityMove entityMovePacket = dynamic_cast<RType::Network::PacketEntityMove &>(packet);
        if (entityMovePacket.getEntityId() != m_clients[endpoint].id) {
            SERVER_LOG_WARN("[{0}:{1}] Invalid entity id", endpoint.address().to_string(), endpoint.port());
            return;
        }
        auto &entity = m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::Transform>(
            entityMovePacket.getEntityId());
        entity.position.x = entityMovePacket.getX();
        entity.position.y = entityMovePacket.getY();
        entity.rotation.x = entityMovePacket.getXDir();
        entity.rotation.y = entityMovePacket.getYDir();
    }
} // namespace RType::Server
