/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Packet
*/

#ifndef PACKET_HPP_
#define PACKET_HPP_

#include "NetworkException.hpp"
#include <chrono>
#include <cstring>
#include <vector>

namespace RType::Network
{
    enum PacketType {
        NONE = -1,
        HELLOSERVER = 0,
        HELLOCLIENT = 1,
        BYESERVER = 2,
        PING = 3,
        PLAYERSPAWN = 4,
        PLAYERDIE = 5,
        ENTITYSPAWN = 6,
        ENTITYMOVE = 7,
        ENTITYHIT = 8,
        ENTITYDIE = 9,
        PLAYERLAUNCHBULLET = 10,
        PLAYERHITENTITY = 11,
        IMATEAPOT = 12,
        ACK = 13,
        ALL = 14
    };

    class Packet
    {
    public:
        /**
         * @brief Construct a new Packet object
         * 
         * This constructor is used to create a packet from scratch
         * 
         * @param type of the packet
         */
        Packet(uint8_t type);
        /**
         * @brief Construct a new Packet object
         * 
         * This constructor is used to create a packet from a buffer
         * like a deserialization
         * 
         * @param buffer raw data
         * @param size size of the buffer
         * @param type type of the packet
         */
        Packet(std::vector<char> &buffer, uint32_t size, uint8_t type);
        virtual ~Packet();

        uint32_t getSize() const { return m_size; };
        uint8_t getType() const { return m_type; };
        uint64_t getTimestamp() const { return m_timestamp; };
        uint16_t getDataSize() const { return m_dataSize; };

        /**
         * @brief Serialize the packet
         * 
         * @return std::vector<char> 
         */
        std::vector<char> serialize() const;

        /**
         * @brief Call in serialize(), must be implemented in child class
         * 
         * @return std::vector<char> 
         */
        virtual std::vector<char> serializeData() const = 0;

    protected:
        /**
         * @brief Get size of header
         * 
         * @return uint32_t 
         */
        uint32_t getHeaderSize() const
        {
            return sizeof(uint32_t) + sizeof(uint8_t) + sizeof(uint64_t) + sizeof(uint16_t);
        };

        /**
         * @brief Call in serialize(), serialize the header
         * 
         * @return std::vector<char> 
         */
        std::vector<char> serializeHeader() const;

        uint32_t m_size;
        uint8_t m_type;
        uint64_t m_timestamp;
        uint16_t m_dataSize;

    public:
        /**
         * @brief With a buffer, get the size of the packet
         * 
         * @param buffer raw data
         * @return uint32_t length of the packet
         * @throw PacketException if the buffer is too small
         */
        static uint32_t getPacketSizeFromBuffer(std::vector<char> &buffer);

        /**
         * @brief With a buffer, get the type of the packet
         * 
         * @param buffer raw data
         * @return uint8_t type of the packet
         * @throw PacketException if the buffer is too small
         */
        static uint8_t getPacketTypeFromBuffer(std::vector<char> &buffer);
    };
} // namespace RType::Network

#endif /* !PACKET_HPP_ */
