/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketHelloServer
*/

#include "PacketEntityHit.hpp"

namespace RType::Network
{
    PacketEntityHit::PacketEntityHit(int entityId) : Packet(PacketType::ENTITYHIT), m_entityId(entityId)
    {
        m_dataSize = sizeof(int);
    }

    PacketEntityHit::PacketEntityHit(std::vector<char> &buffer, uint32_t size, uint8_t type)
        : Packet(PacketType::ENTITYHIT), m_entityId(0)
    {
        const char *data = buffer.data();

        data += getHeaderSize();
        std::memcpy(&m_entityId, data, sizeof(int));
    }

    std::vector<char> PacketEntityHit::serializeData() const
    {
        std::vector<char> buffer;

        buffer.resize(sizeof(int));
        char *data = buffer.data();

        std::memcpy(data, &m_entityId, sizeof(int));
        return buffer;
    }
} // namespace RType::Network
