/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketEntityUpdate
*/

#include "PacketEntityUpdate.hpp"

namespace RType::Network
{
    PacketEntityUpdate::PacketEntityUpdate(RType::Utils::UUID entityUuid, const std::string &components)
        : Packet(PacketType::ENTITYUPDATE), m_entityUuid(entityUuid), m_components(components)
    {
        m_dataSize = UUID_SIZE + m_components.size();
    }

    PacketEntityUpdate::PacketEntityUpdate(std::vector<char> &buffer, uint32_t size, uint8_t type)
        : Packet(buffer, size, type), m_components("")
    {
        const char *data = buffer.data();

        data += getHeaderSize();
        m_entityUuid = RType::Utils::UUID(data, UUID_SIZE);
        data += UUID_SIZE;
        m_components = std::string(data, size - getHeaderSize() - UUID_SIZE);
    }

    std::vector<char> PacketEntityUpdate::serializeData() const
    {
        std::vector<char> buffer;

        buffer.resize(UUID_SIZE + m_components.size());
        char *data = buffer.data();

        std::memcpy(data, m_entityUuid.c_str(), UUID_SIZE);
        data += UUID_SIZE;
        std::memcpy(data, m_components.c_str(), m_components.size());

        return buffer;
    }
} // namespace RType::Network
