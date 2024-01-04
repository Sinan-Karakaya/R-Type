/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Viewport
*/

#pragma once

#include "Editor.hpp"
#include "Runtime/ECS/Components/Components.hpp"
#include "Runtime/ECS/Registry.hpp"

#include "Layers/ILayer.hpp"

#include "ShowUtils.hpp"

RType::Runtime::IRuntime *RuntimeEntry();
void RuntimeDestroy(RType::Runtime::IRuntime *runtime);

namespace RType::Editor
{

    using Runtime = RType::Runtime::IRuntime;
    using Registry = RType::Runtime::ECS::Registry;

    class Viewport : public ILayer
    {
    public:
        Viewport(sf::Event &event, RType::Runtime::IRuntime &runtime, RType::Runtime::ECS::Registry &registry)
            : m_event(event), m_runtime(runtime), m_registry(registry)
        {
            OnAttach();
        }
        ~Viewport() override { OnDetach(); }

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnRender() override;

    private:
        sf::RenderTexture m_renderTexture;
        sf::Event &m_event;
        ImVec2 m_contentRegionSize = ImVec2(0, 0);

        RType::Runtime::IRuntime &m_runtime;
        RType::Runtime::ECS::Registry &m_registry;
    };
} // namespace RType::Editor
