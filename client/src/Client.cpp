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
    Client::Client(const std::string &ip, const short &port)
        : window(sf::VideoMode(1920, 1080), "RType")
    {
        this->loadDynamicRuntime();

        if (this->runtime.get() == nullptr)
            return;

        this->window.setFramerateLimit(60);

        this->runtime->Init();
        this->runtime->setProjectPath(".");
        this->networkHandler = std::make_shared<Runtime::ClientNetworkHandler>(this->runtime);
        this->networkHandler->init(ip, port);
        this->runtime->setNetworkHandler(this->networkHandler);
    }

    Client::~Client()
    {
        this->networkHandler->destroy();

        RType::Runtime::AssetManager::reset();

        this->runtime->Destroy();
        this->runtime.reset();
        ASSERT(Utils::Modules::FreeSharedLibrary(m_libHandle), "Failed to free runtime library");
    }

    void Client::run()
    {
        this->networkHandler->sendToServer(RType::Network::PacketHelloServer(std::stof(RTYPE_VERSION), this->runtime->getProjectPath()));

        while (window.isOpen()) {
            sf::Event event {};
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    window.close();
                if (event.type == sf::Event::Resized)
                    runtime->HandleResizeEvent(event);
            }

            window.clear();

            this->runtime->Update(event);
            this->runtime->Render();

            window.draw(this->runtime->GetRenderTextureSprite());

            window.display();
        }

        this->networkHandler->sendToServer(RType::Network::PacketByeServer());
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

        this->runtime = std::shared_ptr<RType::Runtime::IRuntime>(runtimeEntry());
        if (!this->runtime) {
            CLIENT_LOG_CRITICAL("Failed to create runtime instance");
            return;
        }
    }
} // namespace RType::Client
