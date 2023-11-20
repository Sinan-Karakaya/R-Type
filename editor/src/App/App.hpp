#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "imgui-SFML.h"
#include "imgui.h"

#include "RType.hpp"

namespace RType::Editor {

    using Runtime = RType::Runtime::IRuntime;

    class App {
    public:
        App(std::function<Runtime *()> runtimeEntry) : m_runtime(runtimeEntry())
        {
            m_window.create(sf::VideoMode(1280, 720), "RType Editor");
            m_window.setVerticalSyncEnabled(true);
            ASSERT(ImGui::SFML::Init(m_window), "Failed to init ImGui")
            f_setStyle();
        }
        ~App()
        {
            ImGui::SFML::Shutdown();
            m_runtime.reset();
        }

        void Run();

    private:
        void f_setStyle();

    private:
        sf::RenderWindow m_window;
        sf::Event m_event;
        sf::Clock m_deltaClock;
        std::unique_ptr<Runtime> m_runtime;
    };
}