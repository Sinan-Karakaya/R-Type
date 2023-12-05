/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** UDPServer
*/

#ifndef UDPSERVER_HPP_
#define UDPSERVER_HPP_

#include <iostream>
#include "UDP.hpp"

namespace RType::Network {
    class UDPServer : public UDP {
    public:
        UDPServer(short port);
        ~UDPServer() = default;

        void startReceive();

    protected:
    private:
    };
}

#endif /* !UDPSERVER_HPP_ */
