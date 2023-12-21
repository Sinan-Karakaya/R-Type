/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketEntityCreate
*/

#include "PacketEntityCreate.hpp"

namespace RType::Network
{
    PacketEntityCreate::PacketEntityCreate(uint32_t entityId, const std::string &path)
        : Packet(PacketType::ENTITYCREATE), m_entityId(entityId), m_path(path)
    {
        m_dataSize = sizeof(uint32_t) + m_path.size();
    }

    PacketEntityCreate::PacketEntityCreate(std::vector<char> &buffer, uint32_t size, uint8_t type)
        : Packet(buffer, size, type), m_entityId(0), m_path("")
    {
        const char *data = buffer.data();

        data += getHeaderSize();
        std::memcpy(&m_entityId, data, sizeof(uint32_t));
        data += sizeof(uint32_t);
        m_path = std::string(data);
    }

    std::vector<char> PacketEntityCreate::serializeData() const
    {
        std::vector<char> buffer;

        buffer.resize(sizeof(uint32_t) + m_path.size());
        char *data = buffer.data();

        std::memcpy(data, &m_entityId, sizeof(uint32_t));
        data += sizeof(uint32_t);
        std::memcpy(data, m_path.c_str(), m_path.size());
        return buffer;
    }
} // namespace RType::Network
