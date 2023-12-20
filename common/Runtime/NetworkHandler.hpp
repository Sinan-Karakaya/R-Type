/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** NetworkHandler
*/

#ifndef NETWORKHANDLER_HPP_
#define NETWORKHANDLER_HPP_

#include <string>

namespace RType::Network {
    class NetworkHandler {
    public:
        virtual ~NetworkHandler() = default;

        virtual void init(const std::string &ip, const int port) = 0;
        virtual void destroy() = 0;

        virtual void update() = 0;
    };
}

#endif /* !NETWORKHANDLER_HPP_ */
