#include "SceneHierarchy.hpp"

namespace RType::Editor
{
    void SceneHierarchy::OnAttach() {}
    void SceneHierarchy::OnDetach() {}
    void SceneHierarchy::OnUpdate() {}
    void SceneHierarchy::OnRender()
    {
        ImGui::Begin("Scene Hierarchy");
        ImGui::End();
    }
} // namespace RType::Editor
