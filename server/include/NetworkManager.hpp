/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** NetworkManager
*/

#ifndef NETWORKMANAGER_HPP_
#define NETWORKMANAGER_HPP_

#include <thread>

#include "IOContextHolder.hpp"
#include "UDPServer.hpp"

namespace RType
{
    class NetworkManager
    {
    public:
        NetworkManager(const short &port);
        ~NetworkManager();

        void run();
        void stop();

    private:
        Network::IOContextHolder m_ioContext;
        Network::UDPServer m_udpServer;
        std::thread m_thread;
    };
} // namespace RType

#endif /* !NETWORKMANAGER_HPP_ */
