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
        /**
         * @brief Construct a new UDPClient object
         *
         * @param context io_context
         * @param address address of the server (ex: 127.0.0.1)
         * @param port address of the server (ex: 4242)
         * @param localPort local port to bind to (ex: 0), 0 means random
         */
        UDPClient(asio::io_context &context, const std::string &address, short port, short localPort = 0);
        ~UDPClient() override = default;

        /**
         * @brief Send a packet to endpoint defined in
         * constructor (server)
         *
         * @param packet
         */
        void sendToServer(Packet &packet);

        /**
         * @brief Start receiving packets from server
         *
         * @param handler
         */
        void startReceiveFromServer(std::function<void(Packet &, asio::ip::udp::endpoint &endpoint)> handler);

    private:
        asio::ip::udp::endpoint m_serverEndpoint;
    };
} // namespace RType::Network

#endif /* !UDPCLIENT_HPP_ */
