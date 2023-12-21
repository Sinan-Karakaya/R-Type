/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Client header file
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include "Network/Handler/ClientNetworkHandler.hpp"
#include "Runtime/IRuntime.hpp"

#include "SFML/Window.hpp"

#include "Config.hpp"

namespace RType::Client
{
    class Client
    {
    public:
        Client();
        ~Client();

        /**
         * @brief Run the client and open the window
         */
        void run();

    private:
        void loadDynamicRuntime();

        void *m_libHandle;

        std::unique_ptr<Config> m_config;
        std::shared_ptr<Runtime::IRuntime> m_runtime;
        std::shared_ptr<Runtime::ClientNetworkHandler> m_networkHandler;

        std::unique_ptr<sf::RenderWindow> m_window;
    };
} // namespace RType::Client

#endif /* !CLIENT_HPP_ */
