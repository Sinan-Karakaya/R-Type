/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketFactory
*/

#ifndef PACKETFACTORY_HPP_
#define PACKETFACTORY_HPP_

#include "Packet.hpp"
#include "RType.hpp"
#include <memory>

#include "Packets/PacketACK.hpp"
#include "Packets/PacketByeServer.hpp"
#include "Packets/PacketClientInput.hpp"
#include "Packets/PacketControllableMove.hpp"
#include "Packets/PacketEntityCreate.hpp"
#include "Packets/PacketEntityDestroy.hpp"
#include "Packets/PacketEntityHide.hpp"
#include "Packets/PacketEntityMove.hpp"
#include "Packets/PacketEntityShow.hpp"
#include "Packets/PacketHelloClient.hpp"
#include "Packets/PacketHelloServer.hpp"
#include "Packets/PacketKickClient.hpp"
#include "Packets/PacketPing.hpp"
#include "Packets/PacketEntityUpdate.hpp"

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
    };
} // namespace RType::Network

#endif /* !PACKETFACTORY_HPP_ */
