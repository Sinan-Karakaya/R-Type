/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Inspector
*/

#pragma once

#include "Editor.hpp"
#include "Layers/ILayer.hpp"

namespace RType::Editor
{
    class Inspector : public ILayer
    {
    public:
        Inspector(RType::Runtime::IRuntime &runtime, RType::Runtime::ECS::Registry &registry)
            : m_runtime(runtime), m_registry(registry)
        {
            OnAttach();
        }
        ~Inspector() override { OnDetach(); }

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnRender() override;

    private:
        void f_drawTransformComponent();
        void f_drawRigidbodyComponent();
        void f_drawDrawableComponent();
        void f_drawGravityComponent();
        void f_drawCircleShapeComponent();
        void f_drawScriptComponent();
        void f_drawControllableComponent();
        void f_drawTagComponent();

    private:
        RType::Runtime::IRuntime &m_runtime;
        RType::Runtime::ECS::Registry &m_registry;
    };
} // namespace RType::Editor
