#include "Server.hpp"
#include "Config.hpp"

namespace RType
{
    Server::Server()
    {
        try {
            Config config;
            try {
                config.VerifConfig();
            } catch (std::exception &e) {
                throw std::runtime_error(e.what());
            }
            this->m_fileProject = config.getFileProject();
            this->m_port = config.getPort();
            m_libHandle = RType::Utils::Modules::LoadSharedLibrary("runtime");
            ASSERT(m_libHandle, "Failed to load runtime library")

            RType::Runtime::IRuntime *(*runtimeEntry)() =
                (RType::Runtime::IRuntime * (*)()) RType::Utils::Modules::GetFunction(m_libHandle, "RuntimeEntry");
            ASSERT(runtimeEntry, "Failed to get runtime entry point")

            m_runtime = std::unique_ptr<RType::Runtime::IRuntime>(runtimeEntry());
            m_runtime->Init(1920, 1080);
        } catch (std::exception &e) {
            throw std::runtime_error(e.what());
        }
    }

    Server::~Server()
    {
        m_runtime->Destroy();
        m_runtime.reset();
        ASSERT(RType::Utils::Modules::FreeSharedLibrary(m_libHandle), "Failed to free runtime library")
    }

    void Server::Run()
    {
        constexpr int ticksPerSecond = 20;
        const auto tickDuration = std::chrono::milliseconds(1000 / ticksPerSecond);

        this->m_running = true;
        while (this->m_running) {
            // Network logic
            m_runtime->Update();
            std::this_thread::sleep_for(tickDuration);
        }
    }
} // namespace RType
