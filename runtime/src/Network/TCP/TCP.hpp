/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** TCP
*/

#ifndef TCP_HPP_
#define TCP_HPP_

#include <asio.hpp>
#include "RType.hpp"

#include "../PacketFactory.hpp"

namespace RType::Network {
    class TCP {
    public:
        virtual ~TCP() = default;

        void sendData(asio::ip::tcp::socket &socket, const Packet &packet);
        void receiveData(asio::ip::tcp::socket &socket, std::function<void(Packet &)> callback);

    private:
        std::array<char, 4096> m_recvBuffer;

        PacketFactory m_packetFactory;
    };
}

#endif /* !TCP_HPP_ */
