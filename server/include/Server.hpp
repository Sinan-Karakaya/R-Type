#pragma once

#include "RType.hpp"
#include "Runtime/ECS/Components/Components.hpp"
#include "Runtime/ECS/Registry.hpp"
#include "NetworkManager.hpp"
#include <memory>

RType::Runtime::IRuntime *RuntimeEntry();
void RuntimeDestroy(RType::Runtime::IRuntime *runtime);

namespace RType
{
    class Server
    {
        using Runtime = RType::Runtime::IRuntime;
        using Registry = RType::Runtime::ECS::Registry;

    public:
        Server();
        ~Server();
        void Run();

    private:
        std::string m_fileProject;
        unsigned int m_port;
        bool m_running;
        std::unique_ptr<Runtime> m_runtime;
        void *m_libHandle;

        std::unique_ptr<NetworkManager> m_networkManager;
    };
}; // namespace RType
