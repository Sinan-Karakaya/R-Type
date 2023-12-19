/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Client main file
*/

#include "Client.hpp"
#include "PacketManager.hpp"
#include "RType.hpp"

namespace RType::Client
{
    Client::Client(const std::string &ip, const short &port)
        : m_ioContext(), client(*m_ioContext, ip, port), window(sf::VideoMode(1920, 1080), "RType"), runtime(nullptr)
    {
        this->loadDynamicRuntime();

        if (!this->runtime)
            return;

        this->runtime->Init();
        this->packetManager = std::make_shared<PacketManager>(this->runtime, this->client);
        this->client.startReceiveFromServer([&](RType::Network::Packet &packet, asio::ip::udp::endpoint &endpoint) {
            this->packetManager->handlePackets(packet);
        });
        this->m_ioContext.run();
    }

    Client::~Client()
    {
        this->m_ioContext.stop();
    }

    void Client::run()
    {
        this->client.sendToServer(RType::Network::PacketHelloServer(std::stof(RTYPE_VERSION), "RType"));

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

        this->client.sendToServer(RType::Network::PacketByeServer());
    }

    void Client::loadDynamicRuntime()
    {
        void *libHandle = Utils::Modules::LoadSharedLibrary("runtime");
        if (!libHandle) {
            CLIENT_LOG_CRITICAL("Failed to load runtime library");
            return;
        }

        auto *runtimeEntry = (Runtime::IRuntime * (*)()) Utils::Modules::GetFunction(libHandle, "RuntimeEntry");
        if (!runtimeEntry) {
            CLIENT_LOG_CRITICAL("Failed to get runtime entry point");
            return;
        }

        this->runtime = runtimeEntry();
        if (!this->runtime) {
            CLIENT_LOG_CRITICAL("Failed to create runtime instance");
            return;
        }
    }
} // namespace RType::Client
