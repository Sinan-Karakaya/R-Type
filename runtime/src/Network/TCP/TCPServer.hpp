/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** TCPServer
*/

#ifndef TCPSERVER_HPP_
#define TCPSERVER_HPP_

#include <asio.hpp>
#include "RType.hpp"

#include "TCP.hpp"

namespace RType::Network {
    class TCPServer : public TCP {
    public:
        TCPServer(asio::io_context &ioContext, const short port);
        ~TCPServer() override;

        void sendToAll(const Packet &packet);

        void setAcceptCallback(std::function<void(asio::ip::tcp::socket &)> callback) { m_acceptCallback = callback; }
        void setDisconnectCallback(std::function<void(asio::ip::tcp::socket &)> callback) { m_disconnectCallback = callback; }

    private:
        void accept();

        void killSocket(asio::ip::tcp::socket &socket);

        std::vector<std::unique_ptr<asio::ip::tcp::socket>> m_clientSockets;
        std::function<void(asio::ip::tcp::socket &)> m_acceptCallback;
        std::function<void(asio::ip::tcp::socket &)> m_disconnectCallback;

        asio::ip::tcp::acceptor m_acceptor;
        asio::ip::tcp::socket m_socket;
    };
}

#endif /* !TCPSERVER_HPP_ */
