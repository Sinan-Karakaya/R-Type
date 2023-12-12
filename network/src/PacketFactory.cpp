/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketFactory
*/

#include "PacketFactory.hpp"

namespace RType::Network
{
    std::unique_ptr<Packet> PacketFactory::createPacket(std::vector<char> &buffer, std::size_t bytesReceived)
    {
        std::unique_ptr<Packet> packet;

        uint32_t packetSize = Packet::getPacketSizeFromBuffer(buffer);
        if (packetSize > bytesReceived)
            return nullptr;
        uint8_t packetType = Packet::getPacketTypeFromBuffer(buffer);

        switch (packetType) {
        case PacketType::HELLOSERVER:
            packet = std::make_unique<PacketHelloServer>(buffer, packetSize, packetType);
            break;
        case PacketType::HELLOCLIENT:
            packet = std::make_unique<PacketHelloClient>(buffer, packetSize, packetType);
            break;
        case PacketType::BYESERVER:
            packet = std::make_unique<PacketByeServer>(buffer, packetSize, packetType);
            break;
        case PacketType::PING:
            packet = std::make_unique<PacketPing>(buffer, packetSize, packetType);
            break;
        case PacketType::PLAYERSPAWN:
            packet = std::make_unique<PacketPlayerSpawn>(buffer, packetSize, packetType);
            break;
        case PacketType::PLAYERDIE:
            packet = std::make_unique<PacketPlayerDie>(buffer, packetSize, packetType);
            break;
        case PacketType::ENTITYSPAWN:
            packet = std::make_unique<PacketEntitySpawn>(buffer, packetSize, packetType);
            break;
        case PacketType::ENTITYMOVE:
            packet = std::make_unique<PacketEntityMove>(buffer, packetSize, packetType);
            break;
        case PacketType::ENTITYHIT:
            packet = std::make_unique<PacketEntityHit>(buffer, packetSize, packetType);
            break;
        default:
            break;
        }

        return packet;
    }

} // namespace RType::Network
