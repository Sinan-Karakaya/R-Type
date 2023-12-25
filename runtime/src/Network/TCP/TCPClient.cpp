/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** TCPClient
*/

#include "TCPClient.hpp"

namespace RType::Network {
    TCPClient::TCPClient(asio::io_context &ioContext, const std::string &address, const short port)
        : m_socket(ioContext)
    {
        asio::ip::tcp::resolver resolver(ioContext);
        asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(address, std::to_string(port));

        m_serverEndpoint = *endpoints.begin();

        connect();
    }

    TCPClient::~TCPClient()
    {
        m_socket.close();
    }

    void TCPClient::connect()
    {
        m_socket.async_connect(m_serverEndpoint, [this](const asio::error_code &error) {
            if (error) {
                NETWORK_LOG_ERROR("Failed to connect to server: {0}", error.message());
                return;
            }
            NETWORK_LOG_INFO("Connected to server");
        });
    }

    void TCPClient::sendToServer(const Packet &packet)
    {
        sendData(m_socket, packet);
    }

    void TCPClient::receiveFromServer(std::function<void(Packet &)> callback)
    {
        receiveData(m_socket, callback);
    }
}
