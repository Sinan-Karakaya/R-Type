/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** UDPServer
*/

#ifndef UDPSERVER_HPP_
#define UDPSERVER_HPP_

#include "UDP.hpp"
#include <iostream>

namespace RType::Network
{
    class UDPServer : public UDP
    {
    public:
        /**
         * @brief Construct a new UDPServer object
         *
         * @param context io_context
         * @param port port to bind to (ex: 4242)
         */
        UDPServer(asio::io_context &context, short port);
        ~UDPServer() override = default;

        /**
         * @brief Start receiving packets
         *
         * @param handler
         */
        void startReceive(std::function<void(Packet &, asio::ip::udp::endpoint &endpoint)> handler);

    protected:
    private:
    };
} // namespace RType::Network

#endif /* !UDPSERVER_HPP_ */
