/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Packet
*/

#include "Packet.hpp"

namespace RType::Network
{
    Packet::Packet(std::vector<char> &buffer, uint32_t size, uint8_t type) : m_size(size), m_type(type)
    {
        if (buffer.size() < (sizeof(uint32_t) + sizeof(uint8_t) + sizeof(uint64_t) + sizeof(uint16_t)))
            throw PacketException("Packet is too small to be read");
        const char *data = buffer.data();

        data += sizeof(uint32_t) + sizeof(uint8_t);
        std::memcpy(&m_timestamp, data, sizeof(uint64_t));
        data += sizeof(uint64_t);
        std::memcpy(&m_dataSize, data, sizeof(uint16_t));
    }

    Packet::Packet(uint8_t type) : m_size(0), m_type(type), m_dataSize(0)
    {
        m_timestamp =
            std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
                .count();
    }

    Packet::~Packet() {}

    std::vector<char> Packet::serialize() const
    {
        std::vector<char> buffer;

        buffer = serializeHeader();
        buffer.insert(buffer.end(), serializeData().begin(), serializeData().end());

        return buffer;
    }

    std::vector<char> Packet::serializeHeader() const
    {
        std::vector<char> buffer;

        buffer.resize(sizeof(uint32_t) + sizeof(uint8_t) + sizeof(uint64_t) + sizeof(uint16_t));
        char *data = buffer.data();

        uint32_t totalSize = sizeof(uint32_t) + sizeof(uint8_t) + sizeof(uint64_t) + sizeof(uint16_t) + m_dataSize;
        std::memcpy(data, &totalSize, sizeof(uint32_t));
        data += sizeof(uint32_t);
        std::memcpy(data, &m_type, sizeof(uint8_t));
        data += sizeof(uint8_t);
        std::memcpy(data, &m_timestamp, sizeof(uint64_t));
        data += sizeof(uint64_t);
        std::memcpy(data, &m_dataSize, sizeof(uint16_t));

        return buffer;
    }

    /*
     * HELPING STATIC FUNCTIONS
     */

    /**
     * @brief Deserialize the length from packet header and return it
     *
     * @param buffer from read
     * @return uint32_t length of the packet
     */
    uint32_t Packet::getPacketSizeFromBuffer(std::vector<char> &buffer)
    {
        int32_t size = 0;

        if (buffer.size() < sizeof(uint32_t))
            throw PacketException("Packet is too small to be read");
        const char *data = buffer.data();

        std::memcpy(&size, data, sizeof(uint32_t));

        if (size < 0)
            throw PacketException("Packet size is negative");

        return (uint32_t)size;
    }

    /**
     * @brief Deserialize the type from packet header and return it
     *
     * @param buffer from read
     * @return uint8_t type of the packet
     */
    uint8_t Packet::getPacketTypeFromBuffer(std::vector<char> &buffer)
    {
        uint8_t type = 0;

        if (buffer.size() < (sizeof(uint32_t) + sizeof(uint8_t)))
            throw PacketException("Packet is too small to be read");
        const char *data = buffer.data();

        data += sizeof(uint32_t);
        std::memcpy(&type, data, sizeof(uint8_t));

        return type;
    }

} // namespace RType::Network
