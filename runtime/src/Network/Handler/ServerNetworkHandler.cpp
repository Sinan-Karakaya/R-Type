/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** ServerNetworkHandler
*/

#include "ServerNetworkHandler.hpp"

namespace RType::Runtime
{
    ServerNetworkHandler::ServerNetworkHandler(std::shared_ptr<RType::Runtime::IRuntime> &runtime) : m_runtime(runtime)
    {
    }

    ServerNetworkHandler::~ServerNetworkHandler()
    {
        destroy();
    }

    void ServerNetworkHandler::init(const std::string &ip, int port)
    {
        (void)ip;
        m_server = std::make_unique<RType::Network::UDPServer>(*m_ioContextHolder, port);

        m_server->startReceive(
            std::bind(&ServerNetworkHandler::packetsHandler, this, std::placeholders::_1, std::placeholders::_2));
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
                sendToAll(RType::Network::PacketControllableMove(entity, transform.position.x, transform.position.y,
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
                auto &tag = m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::Tag>(entity);
                sendToAll(RType::Network::PacketEntityMove(tag.uuid, transform.position.x, transform.position.y,
                                                           transform.rotation.x, transform.rotation.y));
            })
        }

        for (auto &client : m_clients) {
            if (!client.second.isConnected)
                continue;
            if (Utils::TimeUtils::getCurrentTimeMillis() - client.second.lastAckCheck < 1000)
                continue;
            client.second.lastAckCheck = Utils::TimeUtils::getCurrentTimeMillis();
            if (client.second.wantedAckPackets.empty())
                continue;
            asio::ip::udp::endpoint endpoint = client.first;
            for (auto &packet : client.second.wantedAckPackets) {
                send(*packet, endpoint, false);
            }
        }

        for (auto &inputs : m_clientsInputs) {
            if (inputs.second.empty())
                continue;
            while (!inputs.second.empty()) {
                SKIP_EXCEPTIONS({
                    auto &script =
                        m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::Script>(inputs.first);

                    for (int i = 0; i < 6; i++) {
                        std::string currentPath = script.paths[i];

                        LuaApi::ExecFunction(m_runtime->getLua(),
                                             LuaApi::GetScriptPath(m_runtime->getProjectPath(), currentPath),
                                             "onClientInput", inputs.first, inputs.second.front());
                    }
                })
                inputs.second.pop();
            }
        }
    }

    void ServerNetworkHandler::send(const RType::Network::Packet &packet, asio::ip::udp::endpoint &endpoint, bool ack)
    {
        if (ack) {
            switch (packet.getType()) {
            case RType::Network::HELLOCLIENT:
                m_clients[endpoint].wantedAckPackets.push_back(std::make_shared<RType::Network::PacketHelloClient>(
                    static_cast<const RType::Network::PacketHelloClient &>(packet)));
                break;
            case RType::Network::ENTITYSHOW:
                m_clients[endpoint].wantedAckPackets.push_back(std::make_shared<RType::Network::PacketEntityShow>(
                    static_cast<const RType::Network::PacketEntityShow &>(packet)));
                break;
            case RType::Network::ENTITYHIDE:
                m_clients[endpoint].wantedAckPackets.push_back(std::make_shared<RType::Network::PacketEntityHide>(
                    static_cast<const RType::Network::PacketEntityHide &>(packet)));
                break;
            case RType::Network::ENTITYCREATE:
                m_clients[endpoint].wantedAckPackets.push_back(std::make_shared<RType::Network::PacketEntityCreate>(
                    static_cast<const RType::Network::PacketEntityCreate &>(packet)));
                break;
            case RType::Network::ENTITYDESTROY:
                m_clients[endpoint].wantedAckPackets.push_back(std::make_shared<RType::Network::PacketEntityDestroy>(
                    static_cast<const RType::Network::PacketEntityDestroy &>(packet)));
                break;
            case RType::Network::ENTITYUPDATE:
                m_clients[endpoint].wantedAckPackets.push_back(std::make_shared<RType::Network::PacketEntityUpdate>(
                    static_cast<const RType::Network::PacketEntityUpdate &>(packet)));
                break;
            }
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
        case RType::Network::PacketType::CONTROLLABLEMOVE:
            entityMoveHandler(packet, endpoint);
            break;
        case RType::Network::PacketType::CLIENTINPUT:
            clientInputHandler(packet, endpoint);
            break;
        }
    }

    /*===========================================================================
                                Packets Handling
    ===========================================================================*/

    void ServerNetworkHandler::entityMoveHandler(RType::Network::Packet &packet, asio::ip::udp::endpoint &endpoint)
    {
        RType::Network::PacketControllableMove entityMovePacket =
            static_cast<RType::Network::PacketControllableMove &>(packet);
        if (entityMovePacket.getEntityId() != m_clients[endpoint].id) {
            SERVER_LOG_WARN("[{0}:{1}] Invalid entity id", endpoint.address().to_string(), endpoint.port());
            return;
        }
        // SKIP_EXCEPTIONS({
        //     auto &script = m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::Script>(
        //         entityMovePacket.getEntityId());
        //     bool hasEntityMoveFunction = false;
        //     for (unsigned int i = 0; i < 6; i++) {
        //         std::string currentPath = script.paths[i];

        //         bool returnV = LuaApi::ExecFunction(
        //             m_runtime->getLua(), LuaApi::GetScriptPath(m_runtime->getProjectPath(), currentPath),
        //             "onEntityMove", entityMovePacket.getEntityId(), entityMovePacket.getX(), entityMovePacket.getY(),
        //             entityMovePacket.getXDir(), entityMovePacket.getYDir());
        //         if (returnV)
        //             hasEntityMoveFunction = true;
        //     }
        //     if (!hasEntityMoveFunction)
        //         return;
        // });
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
             it != m_clients[endpoint].wantedAckPackets.end();) {
            if ((*it)->getType() == ackPacket.getPacketType() &&
                (*it)->getTimestamp() == ackPacket.getPacketTimestamp()) {
                it = m_clients[endpoint].wantedAckPackets.erase(it);
            } else {
                ++it;
            }
        }
    }

    void ServerNetworkHandler::clientInputHandler(RType::Network::Packet &packet, asio::ip::udp::endpoint &endpoint)
    {
        RType::Network::PacketClientInput clientInputPacket = static_cast<RType::Network::PacketClientInput &>(packet);

        SKIP_EXCEPTIONS({
            auto &controllable = m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::Controllable>(
                m_clients[endpoint].id);
            if (!controllable.isActive)
                return;
            m_clientsInputs[m_clients[endpoint].id].push(clientInputPacket.getInput());
        });
    }

    /*===========================================================================
                                ServerNetworkClient
    ===========================================================================*/

    ServerNetworkClient &ServerNetworkHandler::initClient(asio::ip::udp::endpoint &endpoint)
    {
        RType::Runtime::ECS::Entity id = m_controllableEntities.back();
        m_controllableEntities.pop_back();
        ServerNetworkClient client = {
            id, Utils::TimeUtils::getCurrentTimeMillis(), true, Utils::TimeUtils::getCurrentTimeMillis(), {}};

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

        for (auto &entity : m_runtime->GetEntities()) {
            SKIP_EXCEPTIONS({
                auto &controllable =
                    m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::Controllable>(entity);
                if (!controllable.isActive)
                    continue;
                auto &transform =
                    m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::Transform>(entity);
                send(RType::Network::PacketEntityShow(entity, transform.position.x, transform.position.y), endpoint);
            })

            SKIP_EXCEPTIONS({
                auto &iacontrollable =
                    m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::IAControllable>(entity);
                if (!iacontrollable.isActive)
                    continue;
                auto &tag = m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::Tag>(entity);
                auto &transform =
                    m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::Transform>(entity);
                send(RType::Network::PacketEntityCreate(tag.uuid, std::string(tag.tag), transform.position.x,
                                                        transform.position.y),
                     endpoint);
            })
        }

        return m_clients[endpoint];
    }

    void ServerNetworkHandler::destroyClient(asio::ip::udp::endpoint &endpoint)
    {
        uint32_t id = m_clients[endpoint].id;

        sendToAll(RType::Network::PacketEntityHide(id));
        m_clients[endpoint].isConnected = false;

        SKIP_EXCEPTIONS({
            auto &controllable =
                m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::Controllable>(id);
            controllable.isActive = false;
        })
        m_controllableEntities.push_back(id);

        m_clients[endpoint].wantedAckPackets.clear();
    }

    void ServerNetworkHandler::clientsTimeoutChecker()
    {
        long currentTimestamp = Utils::TimeUtils::getCurrentTimeMillis();
        for (auto it = m_clients.begin(); it != m_clients.end();) {
            if (currentTimestamp - it->second.lastPing > 5000) {
                SERVER_LOG_INFO("[{0}:{1}] Timeout", it->first.address().to_string(), it->first.port());
                asio::ip::udp::endpoint endpoint = it->first;
                send(RType::Network::PacketKickClient("Timeout"), endpoint);
                destroyClient(endpoint);
                it = m_clients.erase(it);
            } else {
                ++it;
            }
        }
    }

} // namespace RType::Runtime
