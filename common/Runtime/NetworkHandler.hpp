/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** NetworkHandler
*/

#ifndef NETWORKHANDLER_HPP_
#define NETWORKHANDLER_HPP_

#include <string>

namespace RType::Network
{
    class NetworkHandler
    {
    public:
        virtual ~NetworkHandler() = default;

        /**
         * @brief Initializes the network handler with the specified IP address and port.
         *
         * @param ip The IP address to bind the network handler to.
         * @param port The port number to bind the network handler to.
         */
        virtual void init(const std::string &ip, const int port) = 0;
        /**
         * @brief Destroys the network handler.
         *
         * This function is responsible for destroying the network handler object.
         * It should be implemented by derived classes.
         */
        virtual void destroy() = 0;

        /**
         * @brief Updates the network handler.
         *
         * This function is responsible for updating the network handler.
         * It should be implemented by derived classes.
         */
        virtual void update() = 0;
    };
} // namespace RType::Network

#endif /* !NETWORKHANDLER_HPP_ */
