/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketEntityCreate
*/

#include "PacketEntityCreate.hpp"

namespace RType::Network
{
    PacketEntityCreate::PacketEntityCreate(RType::Utils::UUID entityUuid, const std::string &path, float x, float y)
        : Packet(PacketType::ENTITYCREATE), m_entityUuid(entityUuid), m_path(path), m_x(x), m_y(y)
    {
        m_dataSize = UUID_SIZE + m_path.size() + sizeof(float) + sizeof(float);
    }

    PacketEntityCreate::PacketEntityCreate(std::vector<char> &buffer, uint32_t size, uint8_t type)
        : Packet(buffer, size, type), m_path("")
    {
        const char *data = buffer.data();

        data += getHeaderSize();
        m_entityUuid = RType::Utils::UUID(data, UUID_SIZE);
        data += UUID_SIZE;
        std::memcpy(&m_x, data, sizeof(float));
        data += sizeof(float);
        std::memcpy(&m_y, data, sizeof(float));
        data += sizeof(float);
        m_path = std::string(data, size - getHeaderSize() - UUID_SIZE - sizeof(float) - sizeof(float));
    }

    std::vector<char> PacketEntityCreate::serializeData() const
    {
        std::vector<char> buffer;

        buffer.resize(UUID_SIZE + sizeof(float) + sizeof(float) + m_path.size());
        char *data = buffer.data();

        std::memcpy(data, m_entityUuid.c_str(), UUID_SIZE);
        data += UUID_SIZE;
        std::memcpy(data, &m_x, sizeof(float));
        data += sizeof(float);
        std::memcpy(data, &m_y, sizeof(float));
        data += sizeof(float);
        std::memcpy(data, m_path.c_str(), m_path.size());

        return buffer;
    }
} // namespace RType::Network
