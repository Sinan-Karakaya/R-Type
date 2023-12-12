/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketHelloClient
*/

#ifndef PACKETHELLOCLIENT_HPP_
#define PACKETHELLOCLIENT_HPP_

#include "../Packet.hpp"

namespace RType::Network
{
    /**
     * @brief 4.2 PacketHelloClient
     * /---------------------------------------------------------\
     * | Name                           | Size (in bits) | Value |
     * |--------------------------------|----------------|-------|
     * | Type                           | 8              |     2 |
     * \---------------------------------------------------------/
     */
    class PacketHelloClient : public Packet
    {
    public:
        PacketHelloClient();
        PacketHelloClient(std::vector<char> &buffer, uint32_t size, uint8_t type);
        ~PacketHelloClient() override = default;

        std::vector<char> serializeData() const override;
    };
} // namespace RType::Network

#endif /* !PACKETHELLOCLIENT_HPP_ */