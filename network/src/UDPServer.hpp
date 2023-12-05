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
        UDPServer(asio::io_context &context, short port);
        ~UDPServer() override = default;

        void startReceive();

    protected:
    private:
    };
} // namespace RType::Network

#endif /* !UDPSERVER_HPP_ */
