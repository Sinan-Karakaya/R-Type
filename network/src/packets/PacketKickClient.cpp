/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketKickClient
*/

#include "PacketKickClient.hpp"

namespace RType::Network {
    PacketKickClient::PacketKickClient(const std::string &reason)
        : Packet(PacketType::KICKCLIENT), m_reason(reason)
    {
        m_dataSize = m_reason.size();
    }

    PacketKickClient::PacketKickClient(std::vector<char> &buffer, uint32_t size, uint8_t type)
        : Packet(buffer, size, type), m_reason("")
    {
        const char *data = buffer.data();

        data += getHeaderSize();
        m_reason = std::string(data, size - getHeaderSize());
    }

    std::vector<char> PacketKickClient::serializeData() const
    {
        std::vector<char> buffer;

        buffer.resize(m_reason.size());
        char *data = buffer.data();

        std::memcpy(data, m_reason.c_str(), m_reason.size());
        return buffer;
    }

}