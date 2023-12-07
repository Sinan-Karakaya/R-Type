/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PacketHelloClient
*/

#ifndef PACKETHELLOCLIENT_HPP_
#define PACKETHELLOCLIENT_HPP_

#include "Packet.hpp"

namespace RType::Network {
    
        class PacketHelloClient : public Packet {
        public:
            PacketHelloClient();
            PacketHelloClient(std::vector<char> &buffer);
            PacketHelloClient(std::vector<char> &buffer, uint32_t size, uint8_t type);
            ~PacketHelloClient() override = default;
    
            std::vector<char> serializeData() const override;
    
        private:
            std::string m_username;
        };
}

#endif /* !PACKETHELLOCLIENT_HPP_ */
