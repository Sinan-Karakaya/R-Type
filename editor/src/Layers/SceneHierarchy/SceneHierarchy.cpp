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
            m_registry.AddComponent(entity, RType::Runtime::ECS::Components::Tag {.tag = "Default"});
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
            std::string entityName = "(" + std::to_string(entity) + ") " + m_registry.GetComponent<RType::Runtime::ECS::Components::Tag>(entity).tag;
            if (ImGui::Selectable(entityName.c_str(), g_currentEntitySelected == (int32_t)entity)) {
                g_currentEntitySelected = entity;
            }
        }
        if (ImGui::BeginDragDropTarget()) {
            if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("PREFAB_ADD_ENTITY")) {
                auto prefabPath = std::string(static_cast<const char *>(payload->Data));
                auto entity = m_runtime.loadPrefab(prefabPath);
                g_currentEntitySelected = entity;
            }
            ImGui::EndDragDropTarget();
        }
        ImGui::End();
    }
} // namespace RType::Editor
