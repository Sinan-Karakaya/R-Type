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
    }

    void ClientNetworkHandler::destroy()
    {
        m_ioContextHolder.stop();
    }

    void ClientNetworkHandler::update()
    {
        if (Utils::TimeUtils::getCurrentTimeMillis() - m_lastPing > 1000) {
            m_lastPing = Utils::TimeUtils::getCurrentTimeMillis();
            sendToServer(RType::Network::PacketPing());
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
            entityMoveHandler(packet);
            break;
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
        RType::Network::PacketEntityMove &entityMove = static_cast<RType::Network::PacketEntityMove &>(packet);

        SKIP_EXCEPTIONS({
            auto &transform = m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::Transform>(
                entityMove.getEntityId());

            transform.position.x = entityMove.getX();
            transform.position.y = entityMove.getY();
            transform.rotation.x = entityMove.getXDir();
            transform.rotation.y = entityMove.getYDir();
        })

        sendToServer(RType::Network::PacketACK(packet.getType(), packet.getTimestamp()));
    }

    void ClientNetworkHandler::entityCreateHandler(RType::Network::Packet &packet)
    {
        RType::Network::PacketEntityCreate &entityCreate = static_cast<RType::Network::PacketEntityCreate &>(packet);

        RType::Runtime::ECS::Entity e = m_runtime->loadPrefab(entityCreate.getPath());
        SKIP_EXCEPTIONS({
            auto &transform = m_runtime->GetRegistry().GetComponent<RType::Runtime::ECS::Components::Transform>(e);
            transform.position.x = entityCreate.getX();
            transform.position.y = entityCreate.getY();
        })

        sendToServer(RType::Network::PacketACK(packet.getType(), packet.getTimestamp()));
    }

    void ClientNetworkHandler::entityDestroyHandler(RType::Network::Packet &packet)
    {
        RType::Network::PacketEntityDestroy &entityDestroy = static_cast<RType::Network::PacketEntityDestroy &>(packet);

        m_runtime->RemoveEntity(entityDestroy.getEntityId());
        sendToServer(RType::Network::PacketACK(packet.getType(), packet.getTimestamp()));
    }

} // namespace RType::Runtime
