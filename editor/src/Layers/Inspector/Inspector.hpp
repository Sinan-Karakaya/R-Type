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
        /**
         * @brief Draws the transform component.
         */
        void f_drawTransformComponent();
        /**
         * @brief Draws the Rigidbody component.
         */
        void f_drawRigidbodyComponent();
        /**
         * @brief Draws the DrawableComponent.
         */
        void f_drawDrawableComponent();
        /**
         * @brief Draws the CircleShape component.
         */
        void f_drawCircleShapeComponent();
        /**
         * @brief Draws the script component.
         */
        void f_drawScriptComponent();
        /**
         * @brief Draws the controllable component.
         */
        void f_drawControllableComponent();
        /**
         * @brief Draws the TagComponent.
         */
        void f_drawTagComponent();
        /**
         * @brief Draws the IA controllable component.
         */
        void f_drawIaControllableComponent();

    private:
        RType::Runtime::IRuntime &m_runtime;
        RType::Runtime::ECS::Registry &m_registry;
    };
} // namespace RType::Editor
