/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Client header file
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include "PacketManager.hpp"
#include "Runtime/IRuntime.hpp"
#include "SFML/Window.hpp"
#include "UDPClient.hpp"
#include "utils/IOContextHolder.hpp"

namespace RType::Client
{
    class Client
    {
    public:
        Client(const std::string &ip, const short &port);
        ~Client();

        void run();

    private:
        void loadDynamicRuntime();

        std::shared_ptr<PacketManager> packetManager;
        Runtime::IRuntime *runtime;
        Network::IOContextHolder m_ioContext;
        Network::UDPClient client;
        sf::RenderWindow window;
    };
} // namespace RType::Client

#endif /* !CLIENT_HPP_ */
