#include "Server.hpp"
#include "Config.hpp"

namespace RType::Server
{
    Server::Server()
    {
        m_startingTimestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        SERVER_LOG_INFO("Loading server...");
        try {
            SERVER_LOG_INFO("Loading config file...");
            m_config = std::make_unique<Config>("server.properties");

            SERVER_LOG_INFO("Loading runtime library...");
            m_libHandle = RType::Utils::Modules::LoadSharedLibrary("runtime");
            ASSERT(m_libHandle, "Failed to load runtime library")

            SERVER_LOG_INFO("Trying to get runtime entry point...");
            RType::Runtime::IRuntime *(*runtimeEntry)() =
                (RType::Runtime::IRuntime * (*)()) RType::Utils::Modules::GetFunction(m_libHandle, "RuntimeEntry");
            ASSERT(runtimeEntry, "Failed to get runtime entry point")
            SERVER_LOG_INFO("Runtime entry point loaded");

            SERVER_LOG_INFO("Initializing runtime...");
            m_runtime = std::unique_ptr<RType::Runtime::IRuntime>(runtimeEntry());
            m_runtime->Init();
            SERVER_LOG_INFO("Runtime initialized");
        } catch (std::exception &e) {
            throw std::runtime_error(e.what());
        }

        this->m_fileProject = m_config->getField("PROJECT_FILE");
        SERVER_LOG_INFO("Project file: {0}", this->m_fileProject);

        try {
            this->m_port = std::stoi(m_config->getField("PORT"));
        } catch (std::exception &e) {
            throw std::runtime_error("Invalid port");
        }
        if (this->m_port < 1024 || this->m_port > 65535)
            throw std::runtime_error("Invalid port range");
        m_udpServer = std::make_unique<RType::Network::UDPServer>(*m_ioContext, this->m_port);
    }

    Server::~Server()
    {
        SERVER_LOG_INFO("Bye...");
        m_runtime->Destroy();
        m_runtime.reset();
        ASSERT(RType::Utils::Modules::FreeSharedLibrary(m_libHandle), "Failed to free runtime library")
    }

    void Server::run()
    {
        constexpr int ticksPerSecond = 20;
        const auto tickDuration = std::chrono::milliseconds(1000 / ticksPerSecond);

        this->m_running = true;
        m_udpServer->startReceive(
            [this](const RType::Network::Packet &packet, const asio::ip::udp::endpoint &endpoint) {
            std::cout << "Packet received - " << static_cast<int>(packet.getType()) << std::endl;
            switch (packet.getType()) {
                case RType::Network::PacketType::PING:
                    m_udpServer->sendData(RType::Network::PacketPing(), endpoint);
                    break;
            }
        });
        m_ioContext.run();

        long currentTimestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        SERVER_LOG_INFO("Server is running - Start in {0}ms", (currentTimestamp - m_startingTimestamp));
        while (this->m_running) {
            m_runtime->Update();
            std::this_thread::sleep_for(tickDuration);
        }
    }
} // namespace RType
