/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Client header file
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include "Runtime/IRuntime.hpp"
#include "Network/Handler/ClientNetworkHandler.hpp"

#include "SFML/Window.hpp"

namespace RType::Client
{
    class Client
    {
    public:
        Client(const std::string &ip, const short &port);
        ~Client();

        /**
         * @brief Run the client and open the window
         */
        void run();

    private:
        void loadDynamicRuntime();

        void *m_libHandle;

        std::shared_ptr<Runtime::IRuntime> runtime;
        std::shared_ptr<Runtime::ClientNetworkHandler> networkHandler;

        sf::RenderWindow window;
    };
} // namespace RType::Client

#endif /* !CLIENT_HPP_ */
