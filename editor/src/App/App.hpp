#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "imgui-SFML.h"
#include "imgui.h"

#include "RType.hpp"
#include "Layers/ILayer.hpp"
#include "Layers/AllLayers.hpp"

#include "ProjectManager/ProjectManager.hpp"

namespace RType::Editor {

    using Runtime = RType::Runtime::IRuntime;

    class App {
    public:
        App();
        ~App() { ImGui::SFML::Shutdown(); }

        void Run();

    private:
        void f_checkForProjectLoading();
        void f_setStyle();

    private:
        sf::RenderWindow m_window;
        sf::Event m_event;
        sf::Clock m_deltaClock;

        std::vector<std::unique_ptr<ILayer>> m_layers;
    };
}