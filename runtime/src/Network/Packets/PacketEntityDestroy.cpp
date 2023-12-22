/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketEntityDestroy
*/

#include "PacketEntityDestroy.hpp"

namespace RType::Network
{
    PacketEntityDestroy::PacketEntityDestroy(RType::Utils::UUID entityUuid)
        : Packet(PacketType::ENTITYDESTROY), m_entityUuid(entityUuid)
    {
        m_dataSize = UUID_SIZE;
    }

    PacketEntityDestroy::PacketEntityDestroy(std::vector<char> &buffer, uint32_t size, uint8_t type)
        : Packet(buffer, size, type)
    {
        const char *data = buffer.data();

        data += getHeaderSize();
        m_entityUuid = RType::Utils::UUID(data, UUID_SIZE);
    }

    std::vector<char> PacketEntityDestroy::serializeData() const
    {
        std::vector<char> buffer;

        buffer.resize(UUID_SIZE);
        char *data = buffer.data();

        std::memcpy(data, m_entityUuid.c_str(), UUID_SIZE);
        return buffer;
    }
} // namespace RType::Network
