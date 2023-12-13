/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** UDPServer
*/

#include "UDPServer.hpp"

namespace RType::Network
{
    UDPServer::UDPServer(asio::io_context &context, const short &port) : UDP(context, port)
    {
        NETWORK_LOG_INFO("Start UPDServer on port {0}", port);
    }

    void UDPServer::startReceive(const std::function<void(Packet &, asio::ip::udp::endpoint &endpoint)> &handler)
    {
        receiveData(handler);
    }
} // namespace RType::Network
