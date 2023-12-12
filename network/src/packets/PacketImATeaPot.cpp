/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketHelloServer
*/

#include "PacketImATeaPot.hpp"

namespace RType::Network
{
    PacketImATeaPot::PacketImATeaPot() : Packet(PacketType::IMATEAPOT)
    {
    }

    PacketImATeaPot::PacketImATeaPot(std::vector<char> &buffer, uint32_t size, uint8_t type)
        : Packet(PacketType::IMATEAPOT)
    {
    }

    std::vector<char> PacketImATeaPot::serializeData() const
    {
        return std::vector<char>();
    }
} // namespace RType::Network
