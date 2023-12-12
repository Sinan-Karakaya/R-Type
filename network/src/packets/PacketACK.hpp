/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketHelloServer
*/

#ifndef PACKETACK_HPP_
#define PACKETACK_HPP_

#include "../Packet.hpp"

namespace RType::Network
{
    class PacketACK : public Packet
    {
    public:
        PacketACK(uint8_t packetType, u_int64_t timestamp);
        PacketACK(std::vector<char> &buffer, uint32_t size, uint8_t type);
        ~PacketACK() override = default;

        std::vector<char> serializeData() const override;

    private:
        u_int64_t m_timestamp;
        uint8_t m_packetType;
    };
} // namespace RType::Network

#endif /* !PACKETACK_HPP_ */
