/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Packet
*/

#ifndef PACKET_HPP_
#define PACKET_HPP_

#include <vector>
#include <cstring>
#include <chrono>
#include "../NetworkException.hpp"

namespace RType::Network
{
    enum PacketType {
        HELLOSERVER = 0,
        HELLOCLIENT = 1,
        ALL = 2
    };

    class Packet
    {
    public:
        Packet(uint8_t type);
        Packet(std::vector<char> &buffer);
        Packet(std::vector<char> &buffer, uint32_t size, uint8_t type);
        virtual ~Packet();

        uint32_t getSize() const { return m_size; };
        uint8_t getType() const { return m_type; };
        uint64_t getTimestamp() const { return m_timestamp; };
        uint16_t getDataSize() const { return m_dataSize; };

        std::vector<char> serialize() const;
        virtual std::vector<char> serializeData() const = 0;

    protected:
        uint32_t getHeaderSize() const
        {
            return sizeof(uint32_t) + sizeof(uint8_t) + sizeof(uint64_t) + sizeof(uint16_t);
        };
        
        std::vector<char> serializeHeader() const;

        uint32_t m_size;
        uint8_t m_type;
        uint64_t m_timestamp;
        uint16_t m_dataSize;

    public:
        static uint32_t getPacketSizeFromBuffer(std::vector<char> &buffer);
        static uint8_t getPacketTypeFromBuffer(std::vector<char> &buffer);
    };
} // namespace RType::Network

#endif /* !PACKET_HPP_ */
