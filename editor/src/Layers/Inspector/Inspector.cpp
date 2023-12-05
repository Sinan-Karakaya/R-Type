#include "Inspector.hpp"

namespace RType::Editor
{
    void Inspector::OnAttach() {}
    void Inspector::OnDetach() {}
    void Inspector::OnUpdate() {}
    void Inspector::OnRender()
    {
        if (g_currentEntitySelected == -1) {
            ImGui::Begin("Inspector");
            ImGui::End();
            return;
        }

        ImGui::Begin("Inspector");
        ImGui::Text("Entity: %d", g_currentEntitySelected);
        ImGui::Separator();

        f_drawTransformComponent();

        ImGui::End();
    }
    
    void Inspector::f_drawTransformComponent()
    {
        auto &transform = m_registry.GetComponent<RType::Runtime::ECS::Components::Transform>(g_currentEntitySelected);
        ImGui::Text("Transform");
        
        ImGui::Text("Position:");
        ImGui::DragFloat("X##pos", &transform.position.x, 0.1f);
        ImGui::DragFloat("Y##pos", &transform.position.y, 0.1f);

        ImGui::Text("Rotation:");
        ImGui::DragFloat("X##rot", &transform.rotation.x, 0.1f);
        ImGui::DragFloat("Y##rot", &transform.rotation.y, 0.1f);

        ImGui::Text("Scale:");
        ImGui::DragFloat("X##scale", &transform.scale.x, 0.1f);
        ImGui::DragFloat("Y##scale", &transform.scale.y, 0.1f);
    }
} // namespace RType::Editor
