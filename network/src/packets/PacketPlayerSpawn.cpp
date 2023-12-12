/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketHelloServer
*/

#include "PacketPlayerSpawn.hpp"

namespace RType::Network
{
    PacketPlayerSpawn::PacketPlayerSpawn(int entityId, uint8_t color, float x, float y)
        : Packet(PacketType::PLAYERSPAWN), m_entityId(entityId), m_color(color), m_x(x), m_y(y)
    {
        m_dataSize = sizeof(int) + sizeof(uint8_t) + sizeof(float) + sizeof(float);
    }

    PacketPlayerSpawn::PacketPlayerSpawn(std::vector<char> &buffer, uint32_t size, uint8_t type)
        : Packet(buffer, size, type), m_entityId(0), m_color(0), m_x(0), m_y(0)
    {
        const char *data = buffer.data();

        data += getHeaderSize();
        std::memcpy(&m_entityId, data, sizeof(int));
        data += sizeof(int);
        std::memcpy(&m_color, data, sizeof(uint8_t));
        data += sizeof(uint8_t);
        std::memcpy(&m_x, data, sizeof(float));
        data += sizeof(float);
        std::memcpy(&m_y, data, sizeof(float));
    }

    std::vector<char> PacketPlayerSpawn::serializeData() const
    {
        std::vector<char> buffer;

        buffer.resize(sizeof(int) + sizeof(uint8_t) + sizeof(float) + sizeof(float));
        char *data = buffer.data();

        std::memcpy(data, &m_entityId, sizeof(int));
        data += sizeof(int);
        std::memcpy(data, &m_color, sizeof(uint8_t));
        data += sizeof(uint8_t);
        std::memcpy(data, &m_x, sizeof(float));
        data += sizeof(float);
        std::memcpy(data, &m_y, sizeof(float));
        return buffer;
    }

} // namespace RType::Network
