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

namespace RType::Network
{
    class UDP
    {
    public:
        UDP(asio::io_context &io_context, short port);
        virtual ~UDP();

        void sendData(std::vector<char> &data, const asio::ip::udp::endpoint &endpoint);
        void receiveData(std::function<void(std::error_code, std::size_t, std::vector<char> &)> handler);

    protected:
        asio::ip::udp::socket m_socket;

        std::array<char, 4096> m_recvBuffer;
        asio::ip::udp::endpoint m_senderEndpoint;
    };
} // namespace RType::Network

#endif /* !UDP_HPP_ */
