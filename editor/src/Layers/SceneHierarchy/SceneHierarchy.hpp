#pragma once

#include "Editor.hpp"
#include "Layers/ILayer.hpp"

namespace RType::Editor
{
    class SceneHierarchy : public ILayer
    {
    public:
        SceneHierarchy() { OnAttach(); }
        ~SceneHierarchy() override { OnDetach(); }

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnRender() override;
    };
} // namespace RType::Editor
