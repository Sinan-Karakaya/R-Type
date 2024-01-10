/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** ClientNetworkHandler
*/

#include "ClientNetworkHandler.hpp"

namespace RType::Runtime
{
    ClientNetworkHandler::ClientNetworkHandler(std::shared_ptr<RType::Runtime::IRuntime> runtime) : m_runtime(runtime)
    {
    }

    ClientNetworkHandler::~ClientNetworkHandler()
    {
        destroy();
    }

    void ClientNetworkHandler::init(const std::string &ip, int port)
    {
        m_client = std::make_unique<RType::Network::UDPClient>(*m_ioContextHolder, ip, port);

        m_client->receiveData(
            std::bind(&ClientNetworkHandler::packetsHandler, this, std::placeholders::_1, std::placeholders::_2));
        m_ioContextHolder.run();

        m_lastPing = Utils::TimeUtils::getCurrentTimeMillis();
        m_lastReceivedPing = Utils::TimeUtils::getCurrentTimeMillis();
    }

    void ClientNetworkHandler::destroy()
    {
        m_ioContextHolder.stop();
    }

    void ClientNetworkHandler::update()
    {
        if (Utils::TimeUtils::getCurrentTimeMillis() - m_lastReceivedPing > 5000) {
            if (m_onDisconnect)
                m_onDisconnect("Server timeout");
            return;
        }
        if (Utils::TimeUtils::getCurrentTimeMillis() - m_lastPing > 1000) {
            m_lastPing = Utils::TimeUtils::getCurrentTimeMillis();
            sendToServer(RType::Network::PacketPing());
        }

        while (!m_entitiesToDestroy.empty()) {
            for (auto &entity : m_runtime->GetEntities()) {
                auto &tag = m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::Tag>(entity);
                if (tag.uuid == m_entitiesToDestroy.front()) {
                    m_runtime->RemoveEntity(entity);
                    break;
                }
            }
            m_entitiesToDestroy.pop();
        }

        while (!m_entitiesToCreate.empty()) {
            RType::Network::PacketEntityCreate &entityCreate = m_entitiesToCreate.front();
            RType::Runtime::ECS::Entity e = m_runtime->loadPrefab(entityCreate.getPath());
            SKIP_EXCEPTIONS({
                auto &transform = m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::Transform>(e);
                transform.position.x = entityCreate.getX();
                transform.position.y = entityCreate.getY();

                auto &tag = m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::Tag>(e);
                tag.uuid = entityCreate.getEntityUuid();

                auto &iaControllable =
                    m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::IAControllable>(e);
                iaControllable.isActive = true;
            })
            m_entitiesToCreate.pop();
        }
    }

    void ClientNetworkHandler::sendToServer(const RType::Network::Packet &packet)
    {
        m_client->sendToServer(packet);
    }

    void ClientNetworkHandler::packetsHandler(RType::Network::Packet &packet, asio::ip::udp::endpoint &endpoint)
    {
        (void)endpoint;
        switch (packet.getType()) {
        case RType::Network::PING:
            m_latency = Utils::TimeUtils::getCurrentTimeMillis() - m_lastPing;
            m_lastReceivedPing = Utils::TimeUtils::getCurrentTimeMillis();
            break;
        case RType::Network::HELLOCLIENT: {
            RType::Network::PacketHelloClient &helloClient = static_cast<RType::Network::PacketHelloClient &>(packet);
            m_clientEntity = helloClient.getEntityId();
            sendToServer(RType::Network::PacketACK(packet.getType(), packet.getTimestamp()));
            break;
        }
        case RType::Network::ENTITYSHOW:
            entityShowHandler(packet);
            break;
        case RType::Network::ENTITYHIDE:
            entityHideHandler(packet);
            break;
        case RType::Network::ENTITYCREATE:
            entityCreateHandler(packet);
            break;
        case RType::Network::ENTITYDESTROY:
            entityDestroyHandler(packet);
            break;
        case RType::Network::ENTITYMOVE:
        case RType::Network::CONTROLLABLEMOVE:
            entityMoveHandler(packet);
            break;
        case RType::Network::KICKCLIENT: {
            RType::Network::PacketKickClient &kickClient = static_cast<RType::Network::PacketKickClient &>(packet);
            if (m_onDisconnect)
                m_onDisconnect(kickClient.getReason());
            break;
        }
        }
    }

    void ClientNetworkHandler::entityShowHandler(RType::Network::Packet &packet)
    {
        RType::Network::PacketEntityShow &entityShow = static_cast<RType::Network::PacketEntityShow &>(packet);

        SKIP_EXCEPTIONS({
            auto &controllable = m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::Controllable>(
                entityShow.getEntityId());

            controllable.isActive = true;
            if (entityShow.getEntityId() != m_clientEntity) {
                controllable.isServerControl = true;
            }

            auto &transform = m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::Transform>(
                entityShow.getEntityId());

            transform.position.x = entityShow.getX();
            transform.position.y = entityShow.getY();
        })

        sendToServer(RType::Network::PacketACK(packet.getType(), packet.getTimestamp()));
    }

    void ClientNetworkHandler::entityHideHandler(RType::Network::Packet &packet)
    {
        RType::Network::PacketEntityHide &entityHide = static_cast<RType::Network::PacketEntityHide &>(packet);

        SKIP_EXCEPTIONS({
            auto &controllable = m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::Controllable>(
                entityHide.getEntityId());

            controllable.isActive = false;
            controllable.isServerControl = false;
        })

        sendToServer(RType::Network::PacketACK(packet.getType(), packet.getTimestamp()));
    }

    void ClientNetworkHandler::entityMoveHandler(RType::Network::Packet &packet)
    {
        SKIP_EXCEPTIONS({
            RType::Network::PacketEntityMove &entityMove = static_cast<RType::Network::PacketEntityMove &>(packet);
            for (auto &entity : m_runtime->GetEntities()) {
                auto &tag = m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::Tag>(entity);
                if (tag.uuid == entityMove.getEntityUuid()) {
                    auto &transform =
                        m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::Transform>(entity);
                    transform.position.x = entityMove.getX();
                    transform.position.y = entityMove.getY();
                    transform.rotation.x = entityMove.getXDir();
                    transform.rotation.y = entityMove.getYDir();
                    break;
                }
            }
        })

        SKIP_EXCEPTIONS({
            RType::Network::PacketControllableMove &controllableMove =
                static_cast<RType::Network::PacketControllableMove &>(packet);
            auto &transform = m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::Transform>(
                controllableMove.getEntityId());
            transform.position.x = controllableMove.getX();
            transform.position.y = controllableMove.getY();
            transform.rotation.x = controllableMove.getXDir();
            transform.rotation.y = controllableMove.getYDir();
        })
    }

    void ClientNetworkHandler::entityCreateHandler(RType::Network::Packet &packet)
    {
        RType::Network::PacketEntityCreate &entityCreate = static_cast<RType::Network::PacketEntityCreate &>(packet);

        for (auto &entity : m_runtime->GetEntities()) {
            auto &tag = m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::Tag>(entity);
            if (tag.uuid == entityCreate.getEntityUuid()) {
                sendToServer(RType::Network::PacketACK(packet.getType(), packet.getTimestamp()));
                return;
            }
        }

        m_entitiesToCreate.push(entityCreate);
        // RType::Runtime::ECS::Entity e = m_runtime->loadPrefab(entityCreate.getPath());
        // SKIP_EXCEPTIONS({
        //     auto &transform = m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::Transform>(e);
        //     transform.position.x = entityCreate.getX();
        //     transform.position.y = entityCreate.getY();

        //     auto &tag = m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::Tag>(e);
        //     tag.uuid = entityCreate.getEntityUuid();

        //     auto &iaControllable =
        //         m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::IAControllable>(e);
        //     iaControllable.isActive = true;
        // })

        sendToServer(RType::Network::PacketACK(packet.getType(), packet.getTimestamp()));
    }

    void ClientNetworkHandler::entityDestroyHandler(RType::Network::Packet &packet)
    {
        RType::Network::PacketEntityDestroy &entityDestroy = static_cast<RType::Network::PacketEntityDestroy &>(packet);

        m_entitiesToDestroy.push(entityDestroy.getEntityUuid());
        sendToServer(RType::Network::PacketACK(packet.getType(), packet.getTimestamp()));
    }

    void ClientNetworkHandler::entityUpdateHandler(RType::Network::Packet &packet)
    {
        RType::Network::PacketEntityUpdate &entityUpdate = static_cast<RType::Network::PacketEntityUpdate &>(packet);

        for (auto &entity : m_runtime->GetEntities()) {
            auto &tag = m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::Tag>(entity);
            if (tag.uuid == entityUpdate.getEntityUuid()) {
                json j = json::parse(entityUpdate.getComponents());
                Serializer::updateEntity(*m_runtime, entity, j);
            }
        }
        sendToServer(RType::Network::PacketACK(packet.getType(), packet.getTimestamp()));
    }

} // namespace RType::Runtime
