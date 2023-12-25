/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketHelloServer
*/

#ifndef PACKETIMATEAPOT_HPP_
#define PACKETIMATEAPOT_HPP_

#include "Network/Packet.hpp"

namespace RType::Network
{
    class PacketImATeaPot : public Packet
    {
    public:
        PacketImATeaPot();
        PacketImATeaPot(std::vector<char> &buffer, uint32_t size, uint8_t type);
        ~PacketImATeaPot() override = default;

        std::vector<char> serializeData() const override;
    };
} // namespace RType::Network

#endif /* !PACKETIMATEAPOT_HPP_ */
