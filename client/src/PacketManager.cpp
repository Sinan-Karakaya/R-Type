/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** PacketManager main file
*/

#include "Client.hpp"
#include "RType.hpp"
#include "PacketManager.hpp"

namespace RType::Client
{
    PacketManager::PacketManager(Runtime::IRuntime *runtime, Network::UDPClient &client): runtime(runtime), client(client) {}

    PacketManager::~PacketManager() {}

    void PacketManager::handlePackets(Network::Packet &packet)
    {
        switch (packet.getType()) {
        case RType::Network::HELLOCLIENT:
            this->handleHelloClient(packet);
            break;
        case RType::Network::ENTITYSPAWN:
            this->handleEntitySpawn(packet);
            break;
        case RType::Network::ENTITYDIE:
            this->handleEntityDie(packet);
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

        CLIENT_LOG_INFO("Received HELLOCLIENT packet {0}", id);

        this->sendAckPacket(packet);
    }

    void PacketManager::handleEntitySpawn(Network::Packet &packet)
    {
        Network::PacketEntitySpawn entitySpawnPacket = dynamic_cast<Network::PacketEntitySpawn &>(packet);
        uint32_t id = entitySpawnPacket.getEntityId();
        uint8_t type = entitySpawnPacket.getEntityType();
        float x = entitySpawnPacket.getX();
        float y = entitySpawnPacket.getY();

        CLIENT_LOG_INFO("Received ENTITYSPAWN packet {0} {1} {2} {3}", id, type, x, y);

        this->sendAckPacket(packet);
    }

    void PacketManager::handleEntityDie(Network::Packet &packet)
    {
        Network::PacketEntityDie entityDiePacket = dynamic_cast<Network::PacketEntityDie &>(packet);
        uint32_t id = entityDiePacket.getEntityId();

        CLIENT_LOG_INFO("Received ENTITYDIE packet {0}", id);
    }

    void PacketManager::handleEntityMove(Network::Packet &packet)
    {
        Network::PacketEntityMove entityMovePacket = dynamic_cast<Network::PacketEntityMove &>(packet);
        uint32_t id = entityMovePacket.getEntityId();
        float x = entityMovePacket.getX();
        float y = entityMovePacket.getY();

        CLIENT_LOG_INFO("Received ENTITYMOVE packet {0} {1} {2}", id, x, y);
    }

    void PacketManager::sendAckPacket(Network::Packet &packet)
    {
        Network::PacketACK ackPacket(packet.getType(), packet.getTimestamp());
        this->client.sendToServer(ackPacket);
    }
}
