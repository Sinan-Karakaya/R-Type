/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketByeServer
*/

#include "PacketByeServer.hpp"

namespace RType::Network {
    PacketByeServer::PacketByeServer() : Packet(BYESERVER) {}

    PacketByeServer::PacketByeServer(std::vector<char> &buffer, uint32_t size, uint8_t type) : Packet(buffer, size, type) {}

    std::vector<char> PacketByeServer::serializeData() const {
        std::vector<char> buffer;
        return buffer;
    }
}
