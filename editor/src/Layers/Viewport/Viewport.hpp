#pragma once

#include "Editor.hpp"

#include "Layers/ILayer.hpp"

RType::Runtime::IRuntime *RuntimeEntry();
void RuntimeDestroy(RType::Runtime::IRuntime *runtime);

namespace RType::Editor {

    using Runtime = RType::Runtime::IRuntime;

    class Viewport : public ILayer {
    public:
        Viewport() { OnAttach(); }
        ~Viewport() override { OnDetach(); }

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnRender() override;

    private:
        sf::RenderTexture m_renderTexture;
        std::unique_ptr<Runtime> m_runtime;

        void *m_libHandle;
    };
}