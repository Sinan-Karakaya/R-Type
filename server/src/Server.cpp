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

        m_udpServer = std::make_unique<RType::Network::UDPServer>(*m_ioContext, this->m_port);
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
        m_udpServer->startReceive(
            [this](const RType::Network::Packet &packet, const asio::ip::udp::endpoint &endpoint) {
            std::cout << "Received packet from " << endpoint << std::endl;
        });
        m_ioContext.run();
        while (this->m_running) {
            m_runtime->Update();
            std::this_thread::sleep_for(tickDuration);
        }
    }
} // namespace RType
