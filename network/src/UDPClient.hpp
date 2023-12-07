/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** UDPClient
*/

#ifndef UDPCLIENT_HPP_
#define UDPCLIENT_HPP_

#include "UDP.hpp"
#include <iostream>
#include <string>

namespace RType::Network
{
    class UDPClient : public UDP
    {
    public:
        UDPClient(asio::io_context &context, const std::string &address, short port, short localPort = 0);
        ~UDPClient() override = default;

        void sendToServer(std::vector<char> &data);
        void startReceiveFromServer();

    private:
        asio::ip::udp::endpoint m_serverEndpoint;
    };
} // namespace RType::Network

#endif /* !UDPCLIENT_HPP_ */
