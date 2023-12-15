/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** PacketEntitySpawn
*/

#include "PacketEntitySpawn.hpp"

namespace RType::Network
{
    PacketEntitySpawn::PacketEntitySpawn(uint32_t entityId, uint8_t entityType, float x, float y)
        : Packet(PacketType::ENTITYSPAWN), m_entityId(entityId), m_entityType(entityType), m_x(x), m_y(y)
    {
        m_dataSize = sizeof(uint32_t) + sizeof(u_int8_t) + sizeof(float) + sizeof(float);
    }

    PacketEntitySpawn::PacketEntitySpawn(std::vector<char> &buffer, uint32_t size, uint8_t type)
        : Packet(buffer, size, type), m_entityId(0), m_entityType(0), m_x(0), m_y(0)
    {
        const char *data = buffer.data();

        data += getHeaderSize();
        std::memcpy(&m_entityId, data, sizeof(uint32_t));
        data += sizeof(uint32_t);
        std::memcpy(&m_entityType, data, sizeof(u_int8_t));
        data += sizeof(u_int8_t);
        std::memcpy(&m_x, data, sizeof(float));
        data += sizeof(float);
        std::memcpy(&m_y, data, sizeof(float));
    }

    std::vector<char> PacketEntitySpawn::serializeData() const
    {
        std::vector<char> buffer;

        buffer.resize(sizeof(uint32_t) + sizeof(u_int8_t) + sizeof(float) + sizeof(float));
        char *data = buffer.data();

        std::memcpy(data, &m_entityId, sizeof(uint32_t));
        data += sizeof(uint32_t);
        std::memcpy(data, &m_entityType, sizeof(u_int8_t));
        data += sizeof(u_int8_t);
        std::memcpy(data, &m_x, sizeof(float));
        data += sizeof(float);
        std::memcpy(data, &m_y, sizeof(float));
        return buffer;
    }
} // namespace RType::Network
