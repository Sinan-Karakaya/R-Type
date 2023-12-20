/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** PacketManager main file
*/

#include "Client.hpp"
#include "PacketManager.hpp"
#include "RType.hpp"

namespace RType::Client
{
    PacketManager::PacketManager(Runtime::IRuntime &runtime, Network::UDPClient &udpClient, uint32_t &clientId)
        : runtime(runtime), udpClient(udpClient), clientId(clientId)
    {
    }

    PacketManager::~PacketManager() {}

    void PacketManager::handlePackets(Network::Packet &packet)
    {
        switch (packet.getType()) {
        case RType::Network::HELLOCLIENT:
            this->handleHelloClient(packet);
            break;
        case RType::Network::ENTITYSHOW:
            this->handleEntityShow(packet);
            break;
        case RType::Network::ENTITYHIDE:
            this->handleEntityHide(packet);
            break;
        case RType::Network::ENTITYMOVE:
            this->handleEntityMove(packet);
            break;
        default:
            break;
        }
    }

    void PacketManager::handleHelloClient(Network::Packet &packet)
    {
        Network::PacketHelloClient helloClientPacket = dynamic_cast<Network::PacketHelloClient &>(packet);
        uint32_t id = helloClientPacket.getEntityId();

        CLIENT_LOG_INFO("Received PacketHelloClient (id: {0})", id);

        this->clientId = id;
        this->sendAckPacket(packet);
    }

    void PacketManager::handleEntityShow(Network::Packet &packet)
    {
        Network::PacketEntityShow entityShowPacket = dynamic_cast<Network::PacketEntityShow &>(packet);
        uint32_t id = entityShowPacket.getEntityId();
        float x = entityShowPacket.getX();
        float y = entityShowPacket.getY();

        SKIP_EXCEPTIONS({
            Runtime::ECS::Registry &registry = this->runtime.GetRegistry();
            Runtime::ECS::Components::Transform &transform = registry.GetComponent<Runtime::ECS::Components::Transform>(id);
            Runtime::ECS::Components::Controllable &controllable = registry.GetComponent<Runtime::ECS::Components::Controllable>(id);

            transform.position.x = x;
            transform.position.y = y;
            controllable.isActive = true;
            if (id != this->clientId)
                controllable.isServerControl = true;
        })

        CLIENT_LOG_INFO("Received PacketEntitySpawn (id: {0}, x: {1}, y: {2})", id, x, y);

        this->sendAckPacket(packet);
    }

    void PacketManager::handleEntityHide(Network::Packet &packet)
    {
        Network::PacketEntityHide entityHidePacket = dynamic_cast<Network::PacketEntityHide &>(packet);
        uint32_t id = entityHidePacket.getEntityId();

        CLIENT_LOG_INFO("Received ENTITYDIE packet {0}", id);
    }

    void PacketManager::handleEntityMove(Network::Packet &packet)
    {
        Network::PacketEntityMove entityMovePacket = dynamic_cast<Network::PacketEntityMove &>(packet);
        uint32_t id = entityMovePacket.getEntityId();
        float x = entityMovePacket.getX();
        float y = entityMovePacket.getY();

        SKIP_EXCEPTIONS({
            Runtime::ECS::Registry &registry = this->runtime.GetRegistry();
            Runtime::ECS::Components::Transform &transform = registry.GetComponent<Runtime::ECS::Components::Transform>(id);

            transform.position.x = x;
            transform.position.y = y;
        })

        CLIENT_LOG_INFO("Received PacketEntityMove (id: {0}, x: {1}, y: {2})", id, x, y);
    }

    void PacketManager::sendAckPacket(Network::Packet &packet)
    {
        Network::PacketACK ackPacket(packet.getType(), packet.getTimestamp());

        this->udpClient.sendToServer(ackPacket);
    }
} // namespace RType::Client
