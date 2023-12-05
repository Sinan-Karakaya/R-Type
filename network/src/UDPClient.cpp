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

    void UDPClient::sendToServer(std::vector<char> &data)
    {
        sendData(data, m_serverEndpoint);
    }

    void UDPClient::startReceiveFromServer()
    {
        receiveData([this](std::error_code error, std::size_t bytesRecvd, std::vector<char> &receivedData) {
            if (!error && bytesRecvd > 0) {
                std::cout << "Received " << bytesRecvd << " bytes from " << m_senderEndpoint << std::endl;
                std::cout << "Data: " << std::string(receivedData.begin(), receivedData.end()) << std::endl;
            }
        });
    }

} // namespace RType::Network
