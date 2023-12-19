/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Client header file
*/

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

        RType::Runtime::IRuntime *runtime;
        RType::Network::IOContextHolder m_ioContext;
        RType::Network::UDPClient client;
        sf::RenderWindow window;
    };
} // namespace RType::Client
