/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketHelloServer
*/

#include "PacketPlayerHitEntity.hpp"

namespace RType::Network
{
    PacketPlayerHitEntity::PacketPlayerHitEntity(uint32_t entityId, int score)
        : Packet(PacketType::PLAYERHITENTITY), m_entityId(entityId), m_score(score)
    {
        m_dataSize = sizeof(uint32_t) + sizeof(int);
    }

    PacketPlayerHitEntity::PacketPlayerHitEntity(std::vector<char> &buffer, uint32_t size, uint8_t type)
        : Packet(buffer, size, type), m_entityId(0), m_score(0)
    {
        const char *data = buffer.data();

        data += getHeaderSize();
        std::memcpy(&m_entityId, data, sizeof(uint32_t));
        data += sizeof(uint32_t);
        std::memcpy(&m_score, data, sizeof(int));
    }

    std::vector<char> PacketPlayerHitEntity::serializeData() const
    {
        std::vector<char> buffer;

        buffer.resize(sizeof(int));
        char *data = buffer.data();

        std::memcpy(data, &m_entityId, sizeof(uint32_t));
        data += sizeof(uint32_t);
        std::memcpy(data, &m_score, sizeof(int));
        return buffer;
    }
} // namespace RType::Network
