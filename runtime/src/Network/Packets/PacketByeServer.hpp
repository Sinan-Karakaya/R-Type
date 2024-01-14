/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketByeServer
*/

#ifndef PACKETBYESERVER_HPP_
#define PACKETBYESERVER_HPP_

#include "Network/Packet.hpp"

namespace RType::Network
{
    /**
     * @brief 4.3 PacketByeServer
     * /---------------------------------------------------------\
     * | Name                           | Size (in bits) | Value |
     * |--------------------------------|----------------|-------|
     * | Type                           | 8              |     2 |
     * \---------------------------------------------------------/
     */
    class RTYPE_EXPORT PacketByeServer : public Packet
    {
    public:
        PacketByeServer();
        PacketByeServer(std::vector<char> &buffer, uint32_t size, uint8_t type);
        ~PacketByeServer() override = default;

        std::vector<char> serializeData() const override;
    };
} // namespace RType::Network

#endif /* !PACKETBYESERVER_HPP_ */
