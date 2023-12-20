/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketEntityDestroy
*/

#include "PacketEntityDestroy.hpp"

namespace RType::Network {
    PacketEntityDestroy::PacketEntityDestroy(uint32_t entityId)
        : Packet(PacketType::ENTITYDESTROY), m_entityId(entityId)
    {
        m_dataSize = sizeof(uint32_t);
    }

    PacketEntityDestroy::PacketEntityDestroy(std::vector<char> &buffer, uint32_t size, uint8_t type)
        : Packet(buffer, size, type), m_entityId(0)
    {
        const char *data = buffer.data();

        data += getHeaderSize();
        std::memcpy(&m_entityId, data, sizeof(uint32_t));
    }

    std::vector<char> PacketEntityDestroy::serializeData() const
    {
        std::vector<char> buffer;

        buffer.resize(sizeof(uint32_t));
        char *data = buffer.data();

        std::memcpy(data, &m_entityId, sizeof(uint32_t));
        return buffer;
    }
} // namespace RType::Network
