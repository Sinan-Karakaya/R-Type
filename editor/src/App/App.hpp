/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** App
*/

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>

#include "imgui-SFML.h"
#include "imgui.h"

#include "Layers/AllLayers.hpp"
#include "Layers/ILayer.hpp"
#include "RType.hpp"

#include "ProjectManager/ProjectManager.hpp"


namespace RType::Editor
{

    using Runtime = RType::Runtime::IRuntime;
    using Window = RType::Window::IWindow;

    class App
    {
    public:
        App();
        ~App();

        /**
         * @brief Runs the application.
         *
         * This function is responsible for starting the execution of the application.
         * It should be called after all necessary initialization has been performed.
         */
        void Run();

    private:
        /**
         * @brief Checks if a project is being loaded.
         *
         * This function checks if a project is being loaded and performs the necessary actions accordingly.
         */
        void f_checkForProjectLoading();
        /**
         * @brief Sets the style for the application.
         *
         * This function is responsible for setting the style for the application.
         * It can be used to change the appearance of the user interface elements.
         */
        void f_setStyle();
        /**
         * @brief Sets up the development layers.
         *
         * This function is responsible for setting up the development layers in the application.
         * It performs the necessary initialization and configuration for the development environment.
         */
        void f_setupDevLayers();
        /**
         * @brief Checks for shortcuts and performs corresponding actions.
         */
        void f_checkShortcuts();

    private:

        // Abstract window
        std::unique_ptr<RType::Window::Window> m_window_ptr;

        sf::RenderWindow m_window;
        sf::Event m_event;
        sf::Clock m_deltaClock;

        std::unique_ptr<RType::Runtime::IRuntime> m_runtime;
        void *m_libHandle;

        std::vector<std::unique_ptr<ILayer>> m_layers;

        bool m_showDebugWindow = false;
        bool m_showToolbar = false;
    };
} // namespace RType::Editor
