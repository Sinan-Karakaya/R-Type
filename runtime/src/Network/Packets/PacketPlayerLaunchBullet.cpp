/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketHelloServer
*/

#include "PacketPlayerLaunchBullet.hpp"

namespace RType::Network
{
    PacketPlayerLaunchBullet::PacketPlayerLaunchBullet(uint32_t entityId)
        : Packet(PacketType::PLAYERLAUNCHBULLET), m_entityId(entityId)
    {
        m_dataSize = sizeof(uint32_t);
    }

    PacketPlayerLaunchBullet::PacketPlayerLaunchBullet(std::vector<char> &buffer, uint32_t size, uint8_t type)
        : Packet(buffer, size, type), m_entityId(0)
    {
        const char *data = buffer.data();

        data += getHeaderSize();
        std::memcpy(&m_entityId, data, sizeof(uint32_t));
    }

    std::vector<char> PacketPlayerLaunchBullet::serializeData() const
    {
        std::vector<char> buffer;

        buffer.resize(sizeof(uint32_t));
        char *data = buffer.data();

        std::memcpy(data, &m_entityId, sizeof(uint32_t));
        return buffer;
    }
} // namespace RType::Network
