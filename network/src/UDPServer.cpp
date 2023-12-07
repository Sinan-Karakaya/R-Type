/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** UDPServer
*/

#include "UDPServer.hpp"

namespace RType::Network
{
    UDPServer::UDPServer(asio::io_context &context, short port) : UDP(context, port)
    {
        NETWORK_LOG_INFO("UDPServer created with port {0}", port);
    }

    void UDPServer::startReceive(std::function<void(std::error_code, std::size_t, Packet &)> handler)
    {
        receiveData(handler);
    }
} // namespace RType::Network
