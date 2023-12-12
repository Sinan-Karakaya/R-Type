/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketPing
*/

#include "PacketPing.hpp"

namespace RType::Network
{
    PacketPing::PacketPing() : Packet(PING) {}

    PacketPing::PacketPing(std::vector<char> &buffer, uint32_t size, uint8_t type) : Packet(buffer, size, type) {}

    std::vector<char> PacketPing::serializeData() const
    {
        std::vector<char> buffer;
        return buffer;
    }
} // namespace RType::Network
