/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** UDPClient
*/

#include "UDPClient.hpp"

namespace RType::Network
{
    UDPClient::UDPClient(asio::io_context &context, const std::string &address, short port, short localPort)
        : UDP(context, localPort)
    {
        asio::ip::udp::resolver resolver(context);
        asio::ip::udp::resolver::results_type endpoints = resolver.resolve(address, std::to_string(port));

        m_serverEndpoint = *endpoints.begin();

        int localChoosenPort = m_socket.local_endpoint().port();
        NETWORK_LOG_INFO("UDPClient created wih local port {0}", localChoosenPort);
    }

    void UDPClient::sendToServer(Packet &data)
    {
        sendData(data, m_serverEndpoint);
    }

    void UDPClient::startReceiveFromServer(std::function<void(std::error_code, std::size_t, Packet &)> handler)
    {
        receiveData(handler);
    }

} // namespace RType::Network
