#include "SceneHierarchy.hpp"

namespace RType::Editor
{
    void SceneHierarchy::OnAttach() {}
    void SceneHierarchy::OnDetach() {}
    void SceneHierarchy::OnUpdate()
    {
        m_entities = m_runtime.GetEntities();
    }

    void SceneHierarchy::OnRender()
    {
        ImGui::Begin("Scene Hierarchy");
        if (ImGui::Button(ICON_FA_PLUS " Add entity")) {
            auto entity = m_runtime.AddEntity();
            m_registry.AddComponent(entity, RType::Runtime::ECS::Components::Transform {
                                                .position = {0, 0}, .rotation = {0, 0}, .scale = {1, 1}});
        }
        ImGui::SameLine();
        if (ImGui::Button(ICON_FA_TRASH " Delete entity")) {
            if (g_currentEntitySelected != -1) {
                m_runtime.RemoveEntity(g_currentEntitySelected);
                g_currentEntitySelected = -1;
            }
        }
        ImGui::Separator();
        for (auto &entity : m_entities) {
            if (ImGui::Selectable(std::to_string(entity).c_str(), g_currentEntitySelected == entity)) {
                g_currentEntitySelected = entity;
            }
        }
        ImGui::End();
    }
} // namespace RType::Editor
