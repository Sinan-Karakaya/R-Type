/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Client main file
*/

#include "Client.hpp"
#include "RType.hpp"

namespace RType::Client
{
    Client::Client()
    {
        loadDynamicRuntime();

        if (m_runtime.get() == nullptr)
            return;

        m_config = std::make_unique<Config>("client.properties");

        const std::string &ip = m_config->getField("SERVER_IP");
        const int port = std::stoi(m_config->getField("SERVER_PORT"));

        CLIENT_LOG_INFO("Loading runtime...");

        m_runtime->Init();
        m_runtime->setProjectPath(".");

        CLIENT_LOG_INFO("Server IP: {0}:{1}", ip, port);
        m_networkHandler = std::make_shared<Runtime::ClientNetworkHandler>(m_runtime);
        m_networkHandler->init(ip, port);
        m_runtime->setNetworkHandler(m_networkHandler);

        CLIENT_LOG_INFO("Runtime loaded");
        CLIENT_LOG_INFO("Loading window...");
        m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1920, 1080), "R-Type");
        m_window->setFramerateLimit(60);
    }

    Client::~Client()
    {
        m_networkHandler->destroy();

        RType::Runtime::AssetManager::reset();

        m_runtime->Destroy();
        m_runtime.reset();
        ASSERT(Utils::Modules::FreeSharedLibrary(m_libHandle), "Failed to free runtime library");
    }

    void Client::run()
    {
        m_networkHandler->sendToServer(
            RType::Network::PacketHelloServer(std::stof(RTYPE_VERSION), m_runtime->getProjectPath()));

        while (m_window->isOpen()) {
            sf::Event event {};
            while (m_window->pollEvent(event)) {
                if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    m_window->close();
                if (event.type == sf::Event::Resized)
                    m_runtime->HandleResizeEvent(event);
            }

            m_window->clear();

            m_runtime->Update(event);
            m_runtime->Render();

            m_window->draw(m_runtime->GetRenderTextureSprite());

            m_window->display();
        }

        m_networkHandler->sendToServer(RType::Network::PacketByeServer());
    }

    void Client::loadDynamicRuntime()
    {
        m_libHandle = Utils::Modules::LoadSharedLibrary("runtime");
        if (!m_libHandle) {
            CLIENT_LOG_CRITICAL("Failed to load runtime library");
            return;
        }

        auto *runtimeEntry = (Runtime::IRuntime * (*)()) Utils::Modules::GetFunction(m_libHandle, "RuntimeEntry");
        if (!runtimeEntry) {
            CLIENT_LOG_CRITICAL("Failed to get runtime entry point");
            return;
        }

        m_runtime = std::shared_ptr<RType::Runtime::IRuntime>(runtimeEntry());
        if (!m_runtime) {
            CLIENT_LOG_CRITICAL("Failed to create runtime instance");
            return;
        }
    }
} // namespace RType::Client
