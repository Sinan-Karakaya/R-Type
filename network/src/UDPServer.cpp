/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** UDPServer
*/

#include "UDPServer.hpp"

namespace RType::Network
{
    UDPServer::UDPServer(short port) : UDP(port) {}

    void UDPServer::startReceive()
    {
        receiveData([this](std::error_code error, std::size_t bytesRecvd, std::vector<char> &receivedData) {
            if (!error && bytesRecvd > 0) {
                std::cout << "Received " << bytesRecvd << " bytes from " << m_senderEndpoint << std::endl;
                std::cout << "Data: " << std::string(receivedData.begin(), receivedData.end()) << std::endl;
            }
        });
    }
} // namespace RType::Network
