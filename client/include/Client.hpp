/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Client header file
*/

#include "UDPClient.hpp"
#include "Runtime/IRuntime.hpp"
#include "utils/IOContextHolder.hpp"
#include "SFML/Window.hpp"

namespace RType::Client
{
    class Client {
        public:
            Client(const std::string &ip, const short &port);
            ~Client();

            void run();

        private:
            void loadDynamicRuntime();

            RType::Runtime::IRuntime *runtime;
            RType::Network::IOContextHolder m_ioContext;
            RType::Network::UDPClient client;
            sf::RenderWindow window;
    };
}
