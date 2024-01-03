/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Server
*/

#include "Server.hpp"
#include "Config.hpp"

namespace RType::Server
{
    Server::Server()
    {
        m_startingTimestamp =
            std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
                .count();
        SERVER_LOG_INFO("Loading server...");
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
        m_runtime = std::shared_ptr<RType::Runtime::IRuntime>(runtimeEntry());
        m_runtime->Init();
        SERVER_LOG_INFO("Runtime initialized");

        this->m_fileProject = m_config->getField("PROJECT_FILE");
        SERVER_LOG_INFO("Project file: {0}", this->m_fileProject);
        m_runtime->setProjectPath(".");

        m_runtime->setServer(true);

        try {
            this->m_port = std::stoi(m_config->getField("PORT"));
        } catch (std::exception &e) {
            throw std::runtime_error("Invalid port");
        }
        if (this->m_port < 1024 || this->m_port > 65535)
            throw std::runtime_error("Invalid port range");

        m_networkHandler = std::make_shared<RType::Runtime::ServerNetworkHandler>(m_runtime);
    }

    Server::~Server()
    {
        SERVER_LOG_INFO("Bye...");

        m_commandThread.join();

        m_networkHandler->destroy();

        m_runtime->Destroy();
        m_runtime.reset();
        ASSERT_CONDITION(RType::Utils::Modules::FreeSharedLibrary(m_libHandle), 0, "Failed to free runtime library")
    }

    void Server::run()
    {
        constexpr int ticksPerSecond = 24;
        const auto tickDuration = std::chrono::milliseconds(1000 / ticksPerSecond);

        this->m_running = true;

        m_networkHandler->init("127.0.0.1", m_port);
        m_runtime->setNetworkHandler(m_networkHandler);

        m_commandThread = std::thread([&] {
            while (this->m_running) {
                if (std::cin.peek() != EOF) {
                    std::string inputCommand;
                    std::getline(std::cin, inputCommand);
                    handleCommand(inputCommand);
                }
            }
        });

        long currentTimestamp = Utils::getCurrentTimeMillis();
        SERVER_LOG_INFO("Server is running - Start in {0}ms - Stop server with \"stop\"",
                        currentTimestamp - m_startingTimestamp);
        while (this->m_running) {
            long startTimestamp = Utils::getCurrentTimeMillis();

            m_runtime->Update();

            long endTimestamp = Utils::getCurrentTimeMillis();
            if (endTimestamp - startTimestamp > tickDuration.count())
                SERVER_LOG_WARN("Server is overloaded, tick duration: {0}ms", endTimestamp - startTimestamp);
            std::this_thread::sleep_for(tickDuration);
        }
    }

    void Server::handleCommand(const std::string &command)
    {
        if (command == "stop") {
            this->m_running = false;
        } else if (command == "dump") {
            SERVER_LOG_INFO("List of all entities:");
            for (auto &entity : m_runtime->GetEntities()) {
                SERVER_LOG_INFO("- {0}", entity);
            }

        } else {
            SERVER_LOG_WARN("Unknown command: {0}", command);
        }
    }

} // namespace RType::Server
