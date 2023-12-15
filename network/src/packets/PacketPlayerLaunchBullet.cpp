/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketHelloServer
*/

#include "PacketPlayerLaunchBullet.hpp"

namespace RType::Network
{
    PacketPlayerLaunchBullet::PacketPlayerLaunchBullet(uint32_t entityId, float x, float y, float dirX, float dirY)
        : Packet(PacketType::PLAYERLAUNCHBULLET), m_entityId(entityId), m_x(x), m_y(y), m_dirX(dirX), m_dirY(dirY)
    {
        m_dataSize = sizeof(uint32_t) + sizeof(float) + sizeof(float) + sizeof(float) + sizeof(float);
    }

    PacketPlayerLaunchBullet::PacketPlayerLaunchBullet(std::vector<char> &buffer, uint32_t size, uint8_t type)
        : Packet(buffer, size, type), m_entityId(0), m_x(0), m_y(0), m_dirX(0), m_dirY(0)
    {
        const char *data = buffer.data();

        data += getHeaderSize();
        std::memcpy(&m_entityId, data, sizeof(uint32_t));
        data += sizeof(uint32_t);
        std::memcpy(&m_x, data, sizeof(float));
        data += sizeof(float);
        std::memcpy(&m_y, data, sizeof(float));
        data += sizeof(float);
        std::memcpy(&m_dirX, data, sizeof(float));
        data += sizeof(float);
        std::memcpy(&m_dirY, data, sizeof(float));
    }

    std::vector<char> PacketPlayerLaunchBullet::serializeData() const
    {
        std::vector<char> buffer;

        buffer.resize(sizeof(uint32_t) + sizeof(float) + sizeof(float) + sizeof(float) + sizeof(float));
        char *data = buffer.data();

        std::memcpy(data, &m_entityId, sizeof(uint32_t));
        data += sizeof(uint32_t);
        std::memcpy(data, &m_x, sizeof(float));
        data += sizeof(float);
        std::memcpy(data, &m_y, sizeof(float));
        data += sizeof(float);
        std::memcpy(data, &m_dirX, sizeof(float));
        data += sizeof(float);
        std::memcpy(data, &m_dirY, sizeof(float));
        return buffer;
    }
} // namespace RType::Network
