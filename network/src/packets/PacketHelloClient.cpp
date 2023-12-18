/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketHelloClient
*/

#include "PacketHelloClient.hpp"

namespace RType::Network
{

    PacketHelloClient::PacketHelloClient(uint32_t entityId) : Packet(PacketType::HELLOCLIENT), m_entityId(entityId) {}

    PacketHelloClient::PacketHelloClient(std::vector<char> &buffer, uint32_t size, uint8_t type)
        : Packet(buffer, size, type)
    {
    }

    std::vector<char> PacketHelloClient::serializeData() const
    {
        std::vector<char> buffer;

        buffer.resize(sizeof(uint32_t));
        std::memcpy(buffer.data(), &m_entityId, sizeof(uint32_t));
        return buffer;
    }

} // namespace RType::Network
