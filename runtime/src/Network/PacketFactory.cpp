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
        case PacketType::ENTITYSHOW:
            packet = std::make_unique<PacketEntityShow>(buffer, packetSize, packetType);
            break;
        case PacketType::ENTITYHIDE:
            packet = std::make_unique<PacketEntityHide>(buffer, packetSize, packetType);
            break;
        case PacketType::ENTITYMOVE:
            packet = std::make_unique<PacketEntityMove>(buffer, packetSize, packetType);
            break;
        case PacketType::ACK:
            packet = std::make_unique<PacketACK>(buffer, packetSize, packetType);
            break;
        case PacketType::KICKCLIENT:
            packet = std::make_unique<PacketKickClient>(buffer, packetSize, packetType);
            break;
        case PacketType::ENTITYCREATE:
            packet = std::make_unique<PacketEntityCreate>(buffer, packetSize, packetType);
            break;
        case PacketType::ENTITYDESTROY:
            packet = std::make_unique<PacketEntityDestroy>(buffer, packetSize, packetType);
            break;
        case PacketType::CONTROLLABLEMOVE:
            packet = std::make_unique<PacketControllableMove>(buffer, packetSize, packetType);
            break;
        case PacketType::CLIENTINPUT:
            packet = std::make_unique<PacketClientInput>(buffer, packetSize, packetType);
            break;
        case PacketType::ENTITYUPDATE:
            packet = std::make_unique<PacketEntityUpdate>(buffer, packetSize, packetType);
            break;
        case PacketType::CHANGESCENE:
            packet = std::make_unique<PacketChangeScene>(buffer, packetSize, packetType);
            break;
        default:
            NETWORK_LOG_INFO("Unknown packet type: {0}", packetType);
            break;
        }

        return packet;
    }

} // namespace RType::Network
