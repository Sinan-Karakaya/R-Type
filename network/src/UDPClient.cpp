/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** UDPClient
*/

#include "UDPClient.hpp"

namespace RType::Network {
    UDPClient::UDPClient(const std::string &address, short port): UDP(asio::ip::udp::endpoint(asio::ip::make_address(address), port))
    {}

    void UDPClient::sendToServer(std::vector<char> &data)
    {
        sendData(data, m_socket.remote_endpoint());
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

}