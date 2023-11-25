#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "imgui-SFML.h"
#include "imgui.h"

#include "Layers/AllLayers.hpp"
#include "Layers/ILayer.hpp"
#include "RType.hpp"

#include "ProjectManager/ProjectManager.hpp"

namespace RType::Editor
{

using Runtime = RType::Runtime::IRuntime;

class App
{
  public:
    App();
    ~App()
    {
        ImGui::SFML::Shutdown();
    }

    void Run();

  private:
    void f_checkForProjectLoading();
    void f_setStyle();
    void f_setupDevLayers();

  private:
    sf::RenderWindow m_window;
    sf::Event m_event;
    sf::Clock m_deltaClock;

    std::vector<std::unique_ptr<ILayer>> m_layers;
};
} // namespace RType::Editor
