/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketKickClient
*/

#ifndef PACKETKICKCLIENT_HPP_
#define PACKETKICKCLIENT_HPP_

#include "../Packet.hpp"
#include <string>

namespace RType::Network {
    class PacketKickClient : public Packet {
    public:
        PacketKickClient(const std::string &reason);
        PacketKickClient(std::vector<char> &buffer, uint32_t size, uint8_t type);
        ~PacketKickClient() override = default;

        std::vector<char> serializeData() const override;

        const std::string &getReason() const { return m_reason; }

    private:
        std::string m_reason;
    };
}

#endif /* !PACKETKICKCLIENT_HPP_ */
