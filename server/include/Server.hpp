/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Server
*/

#pragma once

#include <list>

#include "RType.hpp"
#include "Runtime/ECS/Components/Components.hpp"
#include "Runtime/ECS/Registry.hpp"

#include "Config.hpp"
#include "Utils.hpp"
#include <memory>

#include "Network/Handler/ServerNetworkHandler.hpp"

RType::Runtime::IRuntime *RuntimeEntry();
void RuntimeDestroy(RType::Runtime::IRuntime *runtime);

namespace RType::Server
{

    class Server
    {
        using Runtime = RType::Runtime::IRuntime;
        using Registry = RType::Runtime::ECS::Registry;

    public:
        /**
         * @brief The Server class represents a server object.
         *
         * This class is responsible for handling server operations.
         * It provides functionality for initializing and managing a server.
         */
        Server();
        ~Server();
        /**
         * @brief Runs the server.
         *
         * This function starts the server and handles incoming client connections.
         * It listens for incoming messages and dispatches them to the appropriate handlers.
         */
        void run();

        /**
         * @brief Handles a command received by the server.
         *
         * This function takes a command as input and performs the necessary actions based on the command.
         *
         * @param command The command to be handled.
         */
        void handleCommand(const std::string &command);

    private:
        long m_startingTimestamp;

        std::string m_projectPath;
        unsigned int m_port;

        bool m_running;
        std::shared_ptr<Runtime> m_runtime;
        void *m_libHandle;

        std::shared_ptr<RType::Runtime::ServerNetworkHandler> m_networkHandler;

        std::unique_ptr<Config> m_config;
        std::thread m_commandThread;
    };
}; // namespace RType::Server
