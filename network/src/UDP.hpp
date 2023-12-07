/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** UDP
*/

#ifndef UDP_HPP_
#define UDP_HPP_

#include <asio.hpp>
#include <string>
#include <vector>

#include "RType.hpp"
#include "packets/PacketFactory.hpp"

namespace RType::Network
{
    class UDP
    {
    public:
        UDP(asio::io_context &io_context, short port);
        virtual ~UDP();

        void sendData(Packet &packet, const asio::ip::udp::endpoint &endpoint, std::function<void(std::error_code, std::size_t)> handler = nullptr);
        void receiveData(std::function<void(Packet &, asio::ip::udp::endpoint &endpoint)> handler);

    protected:
        asio::ip::udp::socket m_socket;

        std::array<char, 4096> m_recvBuffer;
        asio::ip::udp::endpoint m_senderEndpoint;

    private:
        PacketFactory m_packetFactory;
    };
} // namespace RType::Network

#endif /* !UDP_HPP_ */
