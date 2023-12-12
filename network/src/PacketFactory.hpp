/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketFactory
*/

#ifndef PACKETFACTORY_HPP_
#define PACKETFACTORY_HPP_

#include "Packet.hpp"
#include <memory>

#include "packets/PacketByeServer.hpp"
#include "packets/PacketHelloClient.hpp"
#include "packets/PacketHelloServer.hpp"
#include "packets/PacketPing.hpp"
#include "packets/PacketPlayerDie.hpp"
#include "packets/PacketPlayerSpawn.hpp"

namespace RType::Network
{
    class PacketFactory
    {
    public:
        PacketFactory() = default;
        ~PacketFactory() = default;

        /**
         * @brief Create packet from buffer
         *
         * @param buffer raw data
         * @param bytesReceived bytes received from socket, used to check if
         * the packet is complete
         * @return std::unique_ptr<Packet>
         */
        std::unique_ptr<Packet> createPacket(std::vector<char> &buffer, std::size_t bytesReceived);

    private:
    };
} // namespace RType::Network

#endif /* !PACKETFACTORY_HPP_ */
