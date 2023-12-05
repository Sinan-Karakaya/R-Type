#include "Server.hpp"
#include <fstream>

namespace RType {
    Server::Server()
    {
        try {
            VerifConfig();
            m_libHandle = RType::Utils::Modules::LoadSharedLibrary("runtime");
            ASSERT(m_libHandle, "Failed to load runtime library")

            RType::Runtime::IRuntime *(*runtimeEntry)() =
                (RType::Runtime::IRuntime * (*)()) RType::Utils::Modules::GetFunction(m_libHandle, "RuntimeEntry");
            ASSERT(runtimeEntry, "Failed to get runtime entry point")

            m_runtime = std::unique_ptr<RType::Runtime::IRuntime>(runtimeEntry());
            m_runtime->Init(1920, 1080);

            m_registry = std::make_unique<Registry>();
            m_registry->registerComponent<RType::ECS::Components::Transformable>();
            m_registry->registerComponent<RType::ECS::Components::Velocity>();
            m_registry->registerComponent<RType::ECS::Components::Drawable>();
            m_registry->registerComponent<RType::ECS::Components::Controllable>();
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

    void Server::VerifConfig()
    {
        std::ifstream configFile("server.properties");

        if (!configFile.is_open())
            throw std::runtime_error("server.properties not found");
        std::string line;
        while (std::getline(configFile, line)) {
            std::istringstream iss(line);
            std::string key, value;
            std::getline(iss, key, '=');
            std::getline(iss, value);

            if (key == "PORT") {
                try {
                    this->m_port = CheckValidPort(value);
                } catch (std::exception &e) {
                    throw std::runtime_error("Invalid port");
                }
            } else if (key == "PROJECTDIR") {
                try {
                    this->m_fileProject = VerifyFile(value);
                } catch (std::exception &e) {
                    throw std::runtime_error("Invalid file");
                }
            }
        }
        configFile.close();
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

    std::string Server::VerifyFile(const std::string &fileProject)
    {
        std::ifstream configFile(fileProject);

        if (!configFile.is_open())
            throw std::runtime_error("File not found");
        configFile.close();
        if (fileProject.substr(fileProject.find_last_of(".") + 1) != "json")
            throw std::runtime_error("Invalid file");
        return fileProject;
    }

    int Server::CheckValidPort(const std::string &port)
    {
        try {
            std::stoi(port);
        } catch (std::exception &e) {
            throw std::runtime_error("Invalid port");
        }
        int nb = std::stoi(port);
        if (nb < 1024 || nb > 65535)
            throw std::runtime_error("Invalid port");
        return std::stoi(port);
    }
}
