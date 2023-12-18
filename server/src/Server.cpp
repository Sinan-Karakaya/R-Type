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

        try {
            this->m_port = std::stoi(m_config->getField("PORT"));
        } catch (std::exception &e) {
            throw std::runtime_error("Invalid port");
        }
        if (this->m_port < 1024 || this->m_port > 65535)
            throw std::runtime_error("Invalid port range");
        m_udpServer = std::make_unique<RType::Network::UDPServer>(*m_ioContext, this->m_port);

        if (!std::filesystem::exists("project") || !std::filesystem::is_directory("project"))
            throw std::runtime_error("Project directory not found");
        if (!std::filesystem::exists("project/" + m_config->getField("PROJECT_FILE")))
            throw std::runtime_error("Project file not found");
        this->m_fileProject = "project/" + m_config->getField("PROJECT_FILE");
        SERVER_LOG_INFO("Project file: {0}", this->m_fileProject);

        /**
         * @brief Temporary scene loading
         * FOR MVP ONLY, WILL BE REMOVED
         */
        std::string scene = m_config->getField("DEFAULT_SCENE");
        if (!std::filesystem::exists("project/assets/scenes/" + scene))
            throw std::runtime_error("Default scene not found");
        m_runtime->loadScene("project/assets/scenes/" + scene);

        /*
        This is for get all entities with Controllable component
        Entities with Controllable can be controlled by clients
        */
        for (auto &entity : m_runtime->GetEntities()) {
            SKIP_EXCEPTIONS({
                m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::Controllable>(entity);
                m_controlledEntities.push_back(entity);
            })
        }
    }

    Server::~Server()
    {
        SERVER_LOG_INFO("Bye...");

        m_commandThread.join();
        m_ioContext.stop();

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

        m_commandThread = std::thread([&] {
            while (this->m_running) {
                if (std::cin.peek() != EOF) {
                    std::string inputCommand;
                    std::getline(std::cin, inputCommand);
                    handleCommand(inputCommand);
                }
            }
        });

        long currentTimestamp = Utils::getCurrentTimeMillis();
        SERVER_LOG_INFO("Server is running - Start in {0}ms - Stop server with \"stop\"",
                        currentTimestamp - m_startingTimestamp);
        while (this->m_running) {
            long startTimestamp = Utils::getCurrentTimeMillis();

            m_runtime->Update();
            networkClientsTimeoutChecker();

            long endTimestamp = Utils::getCurrentTimeMillis();
            if (endTimestamp - startTimestamp > tickDuration.count())
                SERVER_LOG_WARN("Server is overloaded, tick duration: {0}ms", endTimestamp - startTimestamp);
            std::this_thread::sleep_for(tickDuration);
        }
    }

    void Server::handleCommand(const std::string &command)
    {
        if (command == "stop") {
            this->m_running = false;
        } else if (command == "dump") {
            SERVER_LOG_INFO("List of all connected clients:");
            for (auto &client : m_clients) {
                SERVER_LOG_INFO("[{0}:{1}] EntityId: {2}", client.first.address().to_string(), client.first.port(),
                                client.second.getId());
            }
            SERVER_LOG_INFO("List of all entities:");
            for (auto &entity : m_runtime->GetEntities()) {
                SERVER_LOG_INFO("- {0}", entity);
            }

        } else {
            SERVER_LOG_WARN("Unknown command: {0}", command);
        }
    }

    /*===============================================================================================================

            NETWORK PART OF THE SERVER, MAYBE MOVE IT TO ANOTHER FILE ?

    ===============================================================================================================*/

    void Server::networkHandler(RType::Network::Packet &packet, asio::ip::udp::endpoint &endpoint)
    {
        if (packet.getType() == RType::Network::PacketType::HELLOSERVER) {
            RType::Network::PacketHelloServer helloServerPacket =
                static_cast<RType::Network::PacketHelloServer &>(packet);
            if (helloServerPacket.getVersion() != std::stof(RTYPE_VERSION)) {
                return;
            }

            if (m_clients.contains(endpoint)) {
                sendPacketToClient(RType::Network::PacketHelloClient(m_clients[endpoint].getId()), endpoint);
                SERVER_LOG_INFO("[{0}:{1}] Already connected, resend PacketHelloClient", endpoint.address().to_string(),
                                endpoint.port());
            } else {
                if (m_controlledEntities.empty()) {
                    SERVER_LOG_INFO("[{0}:{1}] Connection refused: Server is full", endpoint.address().to_string(),
                                    endpoint.port());
                    sendPacketToClient(RType::Network::PacketKickClient("Server is full"), endpoint);
                    return;
                }
                Client &client = initClient(endpoint);
                SERVER_LOG_INFO("[{0}:{1}] Connected", endpoint.address().to_string(), endpoint.port());
                RTYPE_LOG_INFO("ECS assigned id {0} to client", client.getId());
            }
            return;
        } else if (!m_clients.contains(endpoint)) {
            return;
        }

        m_clients[endpoint].setLastPing(Utils::getCurrentTimeMillis());
        switch (packet.getType()) {
        case RType::Network::PacketType::BYESERVER:
            SERVER_LOG_INFO("[{0}:{1}] Disconnected", endpoint.address().to_string(), endpoint.port());
            networkClientDisconnect(endpoint);
            m_clients.erase(endpoint);
            break;
        case RType::Network::PacketType::ENTITYMOVE:
            networkEntityMoveHandler(packet, endpoint);
            break;
        case RType::Network::PacketType::IMATEAPOT:
            SERVER_LOG_INFO("[{0}:{1}] I'm a teapot. Dumb client...", endpoint.address().to_string(), endpoint.port());
            break;
        case RType::Network::PacketType::ACK:
            networkAckHandler(packet, endpoint);
            break;
        case RType::Network::PacketType::PING:
            RType::Network::PacketPing ping;
            sendPacketToClient(ping, endpoint);
            break;
        }
    }

    void Server::networkClientsTimeoutChecker()
    {
        long currentTimestamp = Utils::getCurrentTimeMillis();
        for (auto it = m_clients.begin(); it != m_clients.end();) {
            if (currentTimestamp - it->second.getLastPing() > 5000) {
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
        uint32_t id = m_clients[endpoint].getId();

        networkSendAll(RType::Network::PacketEntityDie(id));
        m_clients[endpoint].setConnected(false);
        m_controlledEntities.push_back(id);

        if (m_clientsThreads.contains(endpoint)) {
            if (m_clientsThreads[endpoint].joinable())
                m_clientsThreads[endpoint].join();
            m_clientsThreads.erase(endpoint);
        }
    }

    void Server::networkSendAll(const RType::Network::Packet &packet)
    {
        for (auto &client : m_clients) {
            asio::ip::udp::endpoint endpoint = client.first;
            sendPacketToClient(packet, endpoint);
        }
    }

    void Server::networkEntityMoveHandler(RType::Network::Packet &packet, asio::ip::udp::endpoint &endpoint)
    {
        RType::Network::PacketEntityMove entityMovePacket = static_cast<RType::Network::PacketEntityMove &>(packet);
        if (entityMovePacket.getEntityId() != m_clients[endpoint].getId()) {
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

    void Server::networkAckHandler(RType::Network::Packet &packet, asio::ip::udp::endpoint &endpoint)
    {
        RType::Network::PacketACK ackPacket = static_cast<RType::Network::PacketACK &>(packet);
        for (auto it = m_clients[endpoint].getWantedAckPackets().begin();
             it != m_clients[endpoint].getWantedAckPackets().end(); ++it) {
            if (it->get()->getType() == ackPacket.getPacketType() &&
                it->get()->getTimestamp() == ackPacket.getTimestamp()) {
                m_clients[endpoint].getWantedAckPackets().erase(it);
                return;
            }
        }
    }

    Client &Server::initClient(asio::ip::udp::endpoint &endpoint)
    {
        RType::Runtime::ECS::Entity id = m_controlledEntities.back();
        m_controlledEntities.pop_back();
        Client client(id);

        m_clients.insert({endpoint, client});
        m_clientsThreads.insert(
            {endpoint, std::thread(&Server::clientThread, this, std::ref(m_clients[endpoint]), std::ref(endpoint))});

        sendPacketToClient(RType::Network::PacketHelloClient(client.getId()), endpoint);
        networkSendAll(RType::Network::PacketEntitySpawn(client.getId(), 0, 0, 0));

        return m_clients[endpoint];
    }

    void Server::clientThread(Client &client, asio::ip::udp::endpoint &endpoint)
    {
        long lastAckTimestamp = Utils::getCurrentTimeMillis();
        long lastPosSendTimestamp = Utils::getCurrentTimeMillis();
        RType::Runtime::ECS::Components::Transform lastPos;
        while (client.isConnected()) {
            if (Utils::getCurrentTimeMillis() - lastAckTimestamp > 1000) {
                for (auto &packet : client.getWantedAckPackets()) {
                    m_udpServer->sendData(*packet, endpoint);
                }
                lastAckTimestamp = Utils::getCurrentTimeMillis();
            }

            if (Utils::getCurrentTimeMillis() - lastPosSendTimestamp > 200) {
                auto &entity =
                    m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::Transform>(client.getId());
                if (entity.position.x != lastPos.position.x || entity.position.y != lastPos.position.y ||
                    entity.rotation.x != lastPos.rotation.x || entity.rotation.y != lastPos.rotation.y) {
                    networkSendAll(RType::Network::PacketEntityMove(
                        client.getId(), entity.position.x, entity.position.y, entity.rotation.x, entity.rotation.y));
                    lastPos = entity;
                }
                lastPosSendTimestamp = Utils::getCurrentTimeMillis();
            }
        }
    }

    void Server::sendPacketToClient(const RType::Network::Packet &packet, asio::ip::udp::endpoint &endpoint)
    {
        switch (packet.getType()) {
        case RType::Network::ENTITYSPAWN:
            m_clients[endpoint].getWantedAckPackets().push_back(std::make_shared<RType::Network::PacketEntitySpawn>(
                static_cast<const RType::Network::PacketEntitySpawn &>(packet)));
            break;
        case RType::Network::ENTITYDIE:
            m_clients[endpoint].getWantedAckPackets().push_back(std::make_shared<RType::Network::PacketEntityDie>(
                static_cast<const RType::Network::PacketEntityDie &>(packet)));
            break;
        }
        m_udpServer->sendData(packet, endpoint);
    }

} // namespace RType::Server
