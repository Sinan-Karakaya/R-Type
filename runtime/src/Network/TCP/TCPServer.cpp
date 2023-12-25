/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** TCPServer
*/

#include "TCPServer.hpp"

namespace RType::Network
{
    TCPServer::TCPServer(asio::io_context &ioContext, const short port)
        : m_acceptor(ioContext, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)), m_socket(ioContext)
    {
        NETWORK_LOG_INFO("TCPServer listening on port {0}", port);
        accept();
    }

    TCPServer::~TCPServer()
    {
        m_acceptor.close();
        for (auto &socket : m_clientSockets) {
            socket->shutdown(asio::ip::tcp::socket::shutdown_both);
            socket->close();
        }
    }

    void TCPServer::accept()
    {
        m_acceptor.async_accept(m_socket, [this](const asio::error_code &error) {
            if (error) {
                NETWORK_LOG_ERROR("Failed to accept connection: {0}", error.message());
                return;
            }
            if (m_acceptCallback)
                m_acceptCallback(m_socket);
            else {
                m_clientSockets.emplace_back(std::make_unique<asio::ip::tcp::socket>(std::move(m_socket)));
            }

            accept();
        });
    }

    void TCPServer::sendToAll(const Packet &packet)
    {
        for (auto &socket : m_clientSockets) {
            sendData(*socket, packet);
        }
    }

    void TCPServer::killSocket(asio::ip::tcp::socket &socket)
    {
        socket.shutdown(asio::ip::tcp::socket::shutdown_both);
        socket.close();
        if (m_disconnectCallback)
            m_disconnectCallback(socket);
        for (auto it = m_clientSockets.begin(); it != m_clientSockets.end(); ++it) {
            if (it->get() == &socket) {
                m_clientSockets.erase(it);
                break;
            }
        }
    }

} // namespace RType::Network
