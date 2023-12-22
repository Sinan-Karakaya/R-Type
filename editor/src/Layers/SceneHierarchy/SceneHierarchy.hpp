/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** SceneHierarchy
*/

#pragma once

#include "Editor.hpp"
#include "Layers/ILayer.hpp"

namespace RType::Editor
{
    class SceneHierarchy : public ILayer
    {
    public:
        SceneHierarchy(RType::Runtime::IRuntime &runtime, RType::Runtime::ECS::Registry &registry)
            : m_runtime(runtime), m_registry(registry)
        {
            OnAttach();
        }
        ~SceneHierarchy() override { OnDetach(); }

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnRender() override;

    private:
        RType::Runtime::IRuntime &m_runtime;
        RType::Runtime::ECS::Registry &m_registry;
        std::vector<RType::Runtime::ECS::Entity> &m_entities = m_runtime.GetEntities();
    };
} // namespace RType::Editor
