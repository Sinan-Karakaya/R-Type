/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketHelloClient
*/

#include "PacketHelloClient.hpp"

namespace RType::Network
{

    PacketHelloClient::PacketHelloClient() : Packet(PacketType::HELLOCLIENT) {}

    PacketHelloClient::PacketHelloClient(std::vector<char> &buffer, uint32_t size, uint8_t type)
        : Packet(buffer, size, type)
    {
    }

    std::vector<char> PacketHelloClient::serializeData() const
    {
        return std::vector<char>();
    }

} // namespace RType::Network
