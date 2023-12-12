/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketHelloServer
*/

#include "PacketACK.hpp"

namespace RType::Network
{
    PacketACK::PacketACK(uint8_t packetType, uint64_t timestamp)
        : Packet(PacketType::ACK), m_timestamp(timestamp), m_packetType(packetType)
    {
        m_dataSize = sizeof(uint64_t) + sizeof(uint8_t);
    }

    PacketACK::PacketACK(std::vector<char> &buffer, uint32_t size, uint8_t type)
        : Packet(PacketType::ACK), m_timestamp(0), m_packetType(0)
    {
        const char *data = buffer.data();

        data += getHeaderSize();
        std::memcpy(&m_timestamp, data, sizeof(uint64_t));
        data += sizeof(uint64_t);
        std::memcpy(&m_packetType, data, sizeof(uint8_t));
    }

    std::vector<char> PacketACK::serializeData() const
    {
        std::vector<char> buffer;

        buffer.resize(sizeof(int));
        char *data = buffer.data();

        std::memcpy(data, &m_packetType, sizeof(uint8_t));
        data += sizeof(uint8_t);
        std::memcpy(data, &m_timestamp, sizeof(uint64_t));
        return buffer;
    }
} // namespace RType::Network
