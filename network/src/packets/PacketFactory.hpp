/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketFactory
*/

#ifndef PACKETFACTORY_HPP_
#define PACKETFACTORY_HPP_

#include <memory>
#include "Packet.hpp"

#include "PacketHelloServer.hpp"
#include "PacketHelloClient.hpp"

namespace RType::Network {
    class PacketFactory {
    public:
        PacketFactory() = default;
        ~PacketFactory() = default;

        std::unique_ptr<Packet> createPacket(std::vector<char> &buffer, std::size_t bytesReceived);

    private:
    };
}

#endif /* !PACKETFACTORY_HPP_ */
