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
        Server();
        ~Server();
        void run();

        void handleCommand(const std::string &command);

    private:
        long m_startingTimestamp;

        std::string m_fileProject;
        unsigned int m_port;

        bool m_running;
        std::shared_ptr<Runtime> m_runtime;
        void *m_libHandle;

        std::shared_ptr<RType::Runtime::ServerNetworkHandler> m_networkHandler;

        std::unique_ptr<Config> m_config;
        std::thread m_commandThread;
    };
}; // namespace RType::Server
