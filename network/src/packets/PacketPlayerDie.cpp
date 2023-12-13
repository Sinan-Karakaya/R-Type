/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketHelloServer
*/

#include "PacketPlayerDie.hpp"
#include "PacketPlayerSpawn.hpp"

namespace RType::Network
{
    PacketPlayerDie::PacketPlayerDie(int entityId) : Packet(PacketType::PLAYERDIE), m_entityId(entityId)
    {
        m_dataSize = sizeof(int);
    }

    PacketPlayerDie::PacketPlayerDie(std::vector<char> &buffer, uint32_t size, uint8_t type)
        : Packet(buffer, size, type), m_entityId(0)
    {
        const char *data = buffer.data();

        data += getHeaderSize();
        std::memcpy(&m_entityId, data, sizeof(int));
    }

    std::vector<char> PacketPlayerDie::serializeData() const
    {
        std::vector<char> buffer;

        buffer.resize(sizeof(int));
        char *data = buffer.data();

        std::memcpy(data, &m_entityId, sizeof(int));
        return buffer;
    }
} // namespace RType::Network
