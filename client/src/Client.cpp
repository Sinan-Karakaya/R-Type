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
        : m_ioContext(), client(*m_ioContext, ip, port), window(sf::VideoMode(1920, 1080), "RType"), runtime(nullptr)
    {
        this->loadDynamicRuntime();

        if (!this->runtime)
            return;

        this->runtime->Init();
        this->m_ioContext.run();
        this->client.startReceiveFromServer([&](RType::Network::Packet &packet, asio::ip::udp::endpoint &endpoint) {
            std::cout << "Received packet from " << endpoint.address().to_string() << ":" << endpoint.port()
                      << std::endl;
        });

        this->client.sendToServer(RType::Network::PacketHelloServer(std::stof(RTYPE_VERSION), "RType"));
    }

    Client::~Client()
    {
        this->m_ioContext.stop();
    }

    void Client::run()
    {
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
    }

    void Client::loadDynamicRuntime()
    {
        void *libHandle = RType::Utils::Modules::LoadSharedLibrary("runtime");
        if (!libHandle)
            return RETURN_MACRO({}, CLIENT_LOG_CRITICAL("Failed to load runtime library"));

        auto *runtimeEntry =
            (RType::Runtime::IRuntime * (*)()) RType::Utils::Modules::GetFunction(libHandle, "RuntimeEntry");
        if (!runtimeEntry)
            return RETURN_MACRO({}, CLIENT_LOG_CRITICAL("Failed to get runtime entry point"));

        this->runtime = runtimeEntry();
        if (!this->runtime)
            return RETURN_MACRO({}, CLIENT_LOG_CRITICAL("Failed to create runtime instance"));
    }
} // namespace RType::Client
