#pragma once

#include "Editor.hpp"
#include "Runtime/ECS/Components/Drawable.hpp"
#include "Runtime/ECS/Components/Transforms.hpp"
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
    Viewport()
    {
        OnAttach();
    }
    ~Viewport() override
    {
        OnDetach();
    }

    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate() override;
    void OnRender() override;

  private:
    sf::RenderTexture m_renderTexture;
    std::unique_ptr<Runtime> m_runtime;
    std::unique_ptr<Registry> m_registry;

    void *m_libHandle;
};
} // namespace RType::Editor
