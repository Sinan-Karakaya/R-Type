/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** ServerNetworkHandler
*/

#include "ServerNetworkHandler.hpp"

namespace RType::Runtime {
    ServerNetworkHandler::ServerNetworkHandler(std::shared_ptr<RType::Runtime::IRuntime> &runtime)
        : m_runtime(runtime)
    {
    }

    ServerNetworkHandler::~ServerNetworkHandler()
    {
        destroy();
    }

    void ServerNetworkHandler::init(const std::string &ip, int port)
    {
        (void) ip;
        m_server = std::make_unique<RType::Network::UDPServer>(*m_ioContextHolder, port);

        m_server->startReceive(std::bind(&ServerNetworkHandler::packetsHandler, this, std::placeholders::_1,
                                         std::placeholders::_2));
        m_ioContextHolder.run();

        /*
        We store all the controllable entities. In the actual gameEngine logic (20/12/2023), all entities
        with controllable component represent the players. We need to know that to assign a entity to a client.
        */
        for (auto &entity : m_runtime->GetEntities()) {
            SKIP_EXCEPTIONS({
                m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::Controllable>(entity);
                m_controllableEntities.push_back(entity);
            })
        }
    }

    void ServerNetworkHandler::destroy()
    {
        m_ioContextHolder.stop();
    }

    void ServerNetworkHandler::update()
    {
        for (auto &entity : m_runtime->GetEntities()) {
            SKIP_EXCEPTIONS({
                auto &controllable =
                    m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::Controllable>(entity);
                if (!controllable.isActive)
                    continue;
                auto &transform =
                    m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::Transform>(entity);
                if (m_transformsCache[entity] == transform)
                    continue;
                m_transformsCache[entity] = transform;
                sendToAll(RType::Network::PacketEntityMove(entity, transform.position.x, transform.position.y,
                                                                transform.rotation.x, transform.rotation.y));
            })
            SKIP_EXCEPTIONS({
                auto &iacontrollable =
                    m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::IAControllable>(entity);
                if (!iacontrollable.isActive)
                    continue;
                auto &transform =
                    m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::Transform>(entity);
                if (m_transformsCache[entity] == transform)
                    continue;
                m_transformsCache[entity] = transform;
                sendToAll(RType::Network::PacketEntityMove(entity, transform.position.x, transform.position.y,
                                                                transform.rotation.x, transform.rotation.y));
            })
        }

        for (auto &client : m_clients) {
            if (Utils::TimeUtils::getCurrentTimeMillis() - client.second.lastAckCheck < 1000)
                continue;
            client.second.lastAckCheck = Utils::TimeUtils::getCurrentTimeMillis();
            if (client.second.wantedAckPackets.empty())
                continue;
            asio::ip::udp::endpoint endpoint = client.first;
            for (auto it = client.second.wantedAckPackets.begin(); it != client.second.wantedAckPackets.end();) {
                RTYPE_LOG_INFO("Resend packet {0} to client {1}", (*it)->getType(), client.second.id);
                send(**it, endpoint);
            }
        }
    }

    void ServerNetworkHandler::send(const RType::Network::Packet &packet, asio::ip::udp::endpoint &endpoint)
    {
        switch (packet.getType()) {
            case RType::Network::HELLOCLIENT:
                m_clients[endpoint].wantedAckPackets.push_back(std::make_shared<RType::Network::PacketHelloClient>(static_cast<const RType::Network::PacketHelloClient &>(packet)));
                break;
            case RType::Network::ENTITYSHOW:
                m_clients[endpoint].wantedAckPackets.push_back(std::make_shared<RType::Network::PacketEntityShow>(static_cast<const RType::Network::PacketEntityShow &>(packet)));
                break;
            case RType::Network::ENTITYHIDE:
                m_clients[endpoint].wantedAckPackets.push_back(std::make_shared<RType::Network::PacketEntityHide>(static_cast<const RType::Network::PacketEntityHide &>(packet)));
                break;
            case RType::Network::ENTITYCREATE:
                m_clients[endpoint].wantedAckPackets.push_back(std::make_shared<RType::Network::PacketEntityCreate>(static_cast<const RType::Network::PacketEntityCreate &>(packet)));
                break;
            case RType::Network::ENTITYDESTROY:
                m_clients[endpoint].wantedAckPackets.push_back(std::make_shared<RType::Network::PacketEntityDestroy>(static_cast<const RType::Network::PacketEntityDestroy &>(packet)));
                break;
        }
        m_server->sendData(packet, endpoint);
    }

    void ServerNetworkHandler::sendToAll(const RType::Network::Packet &packet)
    {
        for (auto &client : m_clients) {
            if (client.second.isConnected) {
                asio::ip::udp::endpoint endpoint = client.first;
                send(packet, endpoint);
            }
        }
    }

    void ServerNetworkHandler::packetsHandler(RType::Network::Packet &packet, asio::ip::udp::endpoint &endpoint)
    {
        if (packet.getType() == RType::Network::PacketType::HELLOSERVER) {
            RType::Network::PacketHelloServer helloServerPacket =
                static_cast<RType::Network::PacketHelloServer &>(packet);
            if (helloServerPacket.getVersion() != std::stof(RTYPE_VERSION)) {
                send(RType::Network::PacketKickClient("Wrong version"), endpoint);
                return;
            }

            if (m_clients.contains(endpoint)) {
                send(RType::Network::PacketHelloClient(m_clients[endpoint].id), endpoint);
                SERVER_LOG_INFO("[{0}:{1}] Already connected, resend PacketHelloClient", endpoint.address().to_string(),
                                endpoint.port());
            } else {
                if (m_controllableEntities.empty()) {
                    SERVER_LOG_INFO("[{0}:{1}] Connection refused: Server is full", endpoint.address().to_string(),
                                    endpoint.port());
                    send(RType::Network::PacketKickClient("Server is full"), endpoint);
                    return;
                }
                ServerNetworkClient &client = initClient(endpoint);
                SERVER_LOG_INFO("[{0}:{1}] Connected", endpoint.address().to_string(), endpoint.port());
                RTYPE_LOG_INFO("ECS assigned id {0} to client", client.id);
            }
            return;
        } else if (!m_clients.contains(endpoint)) {
            return;
        }

        m_clients[endpoint].lastPing = Utils::TimeUtils::getCurrentTimeMillis();
        switch (packet.getType()) {
        case RType::Network::PacketType::BYESERVER:
            SERVER_LOG_INFO("[{0}:{1}] Disconnected", endpoint.address().to_string(), endpoint.port());
            destroyClient(endpoint);
            m_clients.erase(endpoint);
            break;
        case RType::Network::PacketType::ACK:
            ackHandler(packet, endpoint);
            break;
        case RType::Network::PacketType::PING:
            send(RType::Network::PacketPing(), endpoint);
            break;
        // For now, we handle this case here but to the future, I want to put directly in system
        case RType::Network::PacketType::ENTITYMOVE:
            entityMoveHandler(packet, endpoint);
            break;
        }
    }

    /*===========================================================================
                                Packets Handling
    ===========================================================================*/

    void ServerNetworkHandler::entityMoveHandler(RType::Network::Packet &packet, asio::ip::udp::endpoint &endpoint)
    {
        RType::Network::PacketEntityMove entityMovePacket = static_cast<RType::Network::PacketEntityMove &>(packet);
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

    void ServerNetworkHandler::ackHandler(RType::Network::Packet &packet, asio::ip::udp::endpoint &endpoint)
    {
        RType::Network::PacketACK ackPacket = static_cast<RType::Network::PacketACK &>(packet);
        for (auto it = m_clients[endpoint].wantedAckPackets.begin();
             it != m_clients[endpoint].wantedAckPackets.end(); ++it) {
            if (it->get()->getType() == ackPacket.getPacketType() &&
                it->get()->getTimestamp() == ackPacket.getTimestamp()) {
                m_clients[endpoint].wantedAckPackets.erase(it);
                return;
            }
        }
    }

    /*===========================================================================
                                ServerNetworkClient
    ===========================================================================*/

    ServerNetworkClient &ServerNetworkHandler::initClient(asio::ip::udp::endpoint &endpoint)
    {
        RType::Runtime::ECS::Entity id = m_controllableEntities.back();
        m_controllableEntities.pop_back();
        ServerNetworkClient client = {id, Utils::TimeUtils::getCurrentTimeMillis(), {}, true, Utils::TimeUtils::getCurrentTimeMillis()};

        SKIP_EXCEPTIONS({
            auto &controllable =
                m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::Controllable>(id);
            controllable.isActive = true;
        })
        m_clients.insert({endpoint, client});

        send(RType::Network::PacketHelloClient(client.id), endpoint);
        SKIP_EXCEPTIONS({
            auto &transform = m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::Transform>(id);
            sendToAll(RType::Network::PacketEntityShow(client.id, transform.position.x, transform.position.y));
        })

        for (auto &client : m_clients) {
            if (client.first != endpoint) {
                SKIP_EXCEPTIONS({
                    auto &transform = m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::Transform>(id);
                    send(RType::Network::PacketEntityShow(client.second.id, transform.position.x, transform.position.y), endpoint);
                })
            }
        }
        
        return m_clients[endpoint];
    }

    void ServerNetworkHandler::destroyClient(asio::ip::udp::endpoint &endpoint)
    {
        uint32_t id = m_clients[endpoint].id;

        sendToAll(RType::Network::PacketEntityHide(id));
        m_clients[endpoint].isConnected = true;

        SKIP_EXCEPTIONS({
            auto &controllable =
                m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::Controllable>(id);
            controllable.isActive = false;
        })
        m_controllableEntities.push_back(id);
    }

    void ServerNetworkHandler::clientsTimeoutChecker()
    {
        long currentTimestamp = Utils::TimeUtils::getCurrentTimeMillis();
        for (auto it = m_clients.begin(); it != m_clients.end();) {
            if (currentTimestamp - it->second.lastPing > 5000) {
                SERVER_LOG_INFO("[{0}:{1}] Timeout", it->first.address().to_string(), it->first.port());
                asio::ip::udp::endpoint endpoint = it->first;
                destroyClient(endpoint);
                it = m_clients.erase(it);
            } else {
                ++it;
            }
        }
    }

}