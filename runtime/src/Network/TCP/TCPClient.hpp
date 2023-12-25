/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** TCPClient
*/

#ifndef TCPCLIENT_HPP_
#define TCPCLIENT_HPP_

#include "RType.hpp"
#include <asio.hpp>

#include "TCP.hpp"

namespace RType::Network
{
    class TCPClient : public TCP
    {
    public:
        TCPClient(asio::io_context &ioContext, const std::string &address, const short port);
        ~TCPClient() override;

        void sendToServer(const Packet &packet);
        void receiveFromServer(std::function<void(Packet &)> callback);

    private:
        void connect();

        asio::ip::tcp::socket m_socket;
        asio::ip::tcp::endpoint m_serverEndpoint;
    };
} // namespace RType::Network

#endif /* !TCPCLIENT_HPP_ */
