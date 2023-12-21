/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketEntityCreate
*/

#include "PacketEntityCreate.hpp"

namespace RType::Network
{
    PacketEntityCreate::PacketEntityCreate(uint32_t entityId, const std::string &path, float x, float y)
        : Packet(PacketType::ENTITYCREATE), m_entityId(entityId), m_path(path), m_x(x), m_y(y)
    {
        m_dataSize = sizeof(uint32_t) + m_path.size() + sizeof(float) + sizeof(float);
    }

    PacketEntityCreate::PacketEntityCreate(std::vector<char> &buffer, uint32_t size, uint8_t type)
        : Packet(buffer, size, type), m_entityId(0), m_path("")
    {
        const char *data = buffer.data();

        data += getHeaderSize();
        std::memcpy(&m_entityId, data, sizeof(uint32_t));
        data += sizeof(uint32_t);
        std::memcpy(&m_x, data, sizeof(float));
        data += sizeof(float);
        std::memcpy(&m_y, data, sizeof(float));
        data += sizeof(float);
        m_path = std::string(data, size - getHeaderSize() - sizeof(uint32_t) - sizeof(float) - sizeof(float));
    }

    std::vector<char> PacketEntityCreate::serializeData() const
    {
        std::vector<char> buffer;

        buffer.resize(sizeof(uint32_t) + sizeof(float) + sizeof(float) + m_path.size());
        char *data = buffer.data();

        std::memcpy(data, &m_entityId, sizeof(uint32_t));
        data += sizeof(uint32_t);
        std::memcpy(data, &m_x, sizeof(float));
        data += sizeof(float);
        std::memcpy(data, &m_y, sizeof(float));
        data += sizeof(float);
        std::memcpy(data, m_path.c_str(), m_path.size());

        return buffer;
    }
} // namespace RType::Network
