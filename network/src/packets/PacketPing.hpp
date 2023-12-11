/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketPing
*/

#ifndef PACKETPING_HPP_
#define PACKETPING_HPP_

#include "../Packet.hpp"

namespace RType::Network {
    /**
     * @brief 4.4 PacketPing
     * /---------------------------------------------------------\
     * | Name                           | Size (in bits) | Value |
     * |--------------------------------|----------------|-------|
     * | Type                           | 8              |     3 |
     * \---------------------------------------------------------/
     */
    class PacketPing : public Packet {
    public:
        PacketPing();
        PacketPing(std::vector<char> &buffer, uint32_t size, uint8_t type);
        ~PacketPing() override = default;

        std::vector<char> serializeData() const override;
    };
}

#endif /* !PACKETPING_HPP_ */
