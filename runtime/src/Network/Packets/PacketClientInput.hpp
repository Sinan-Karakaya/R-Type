/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketClientInput
*/

#ifndef PACKETCLIENTINPUT_HPP_
#define PACKETCLIENTINPUT_HPP_

#include "Network/Packet.hpp"

namespace RType::Network {
    class PacketClientInput : public Packet {
    public:
        PacketClientInput(const std::string &input);
        PacketClientInput(std::vector<char> &buffer, uint32_t size, uint8_t type);
        ~PacketClientInput() override = default;

        std::vector<char> serializeData() const override;

        std::string getInput() const { return m_input; }

    private:
        std::string m_input;
    };
}

#endif /* !PACKETCLIENTINPUT_HPP_ */
