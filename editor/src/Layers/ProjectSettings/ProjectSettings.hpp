/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** ProjectSettings
*/

#ifndef PROJECTSETTINGS_HPP_
#define PROJECTSETTINGS_HPP_

#include <nlohmann/json.hpp>

#include "Editor.hpp"
#include "Layers/ILayer.hpp"

#include "Runtime/ECS/Components/Components.hpp"
#include "Runtime/ECS/Registry.hpp"

namespace RType::Editor {
    using Runtime = RType::Runtime::IRuntime;
    using Registry = RType::Runtime::ECS::Registry;
    using json = nlohmann::json;

    class ProjectSettings : public ILayer
    {
    public:
        ProjectSettings(RType::Runtime::IRuntime &runtime, RType::Runtime::ECS::Registry &registry)
            : m_runtime(runtime), m_registry(registry)
        {
            OnAttach();
        }
        ~ProjectSettings() override { OnDetach(); }

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnRender() override;

    private:
        RType::Runtime::IRuntime &m_runtime;
        RType::Runtime::ECS::Registry &m_registry;
    };
}

#endif /* !PROJECTSETTINGS_HPP_ */
