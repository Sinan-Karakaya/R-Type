#pragma once

#include "Editor.hpp"
#include "Runtime/ECS/Components/Components.hpp"
#include "Runtime/ECS/Registry.hpp"

#include "Layers/ILayer.hpp"

RType::Runtime::IRuntime *RuntimeEntry();
void RuntimeDestroy(RType::Runtime::IRuntime *runtime);

namespace RType::Editor
{

    using Runtime = RType::Runtime::IRuntime;
    using Registry = RType::Runtime::ECS::Registry;

    class Viewport : public ILayer
    {
    public:
        Viewport(sf::Event &event) : m_event(event) { OnAttach(); }
        ~Viewport() override { OnDetach(); }

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnRender() override;

    private:
        sf::RenderTexture m_renderTexture;
        sf::Event &m_event;

        std::unique_ptr<Runtime> m_runtime;

        void *m_libHandle;
    };
} // namespace RType::Editor
