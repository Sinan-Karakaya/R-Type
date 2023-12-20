#include "Viewport.hpp"

namespace RType::Editor
{
    void Viewport::OnAttach() {}

    void Viewport::OnDetach()
    {
        m_runtime.Destroy();
    }

    void Viewport::OnUpdate()
    {
        if (!m_runtime.isPaused())
            m_runtime.Update(m_event);
        if (m_contentRegionSize.x > 0 && m_contentRegionSize.y > 0) {
            m_runtime.HandleResizeEvent(m_contentRegionSize.x, m_contentRegionSize.y);
        }
        m_runtime.Render();
    }

    void Viewport::OnRender()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::Begin("Viewport");
        ImVec2 contentRegion = ImGui::GetWindowSize();
        m_contentRegionSize = contentRegion;
        ImGui::Image(m_runtime.GetRenderTexture());
        if (ImGui::BeginDragDropTarget()) {
            if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("PREFAB_ADD_ENTITY")) {
                auto prefabPath = std::string(static_cast<const char *>(payload->Data));
                auto entity = m_runtime.loadPrefab(prefabPath);
                g_currentEntitySelected = entity;
            }
            ImGui::EndDragDropTarget();
        }

        ImGui::End();
        ImGui::PopStyleVar();
    }
} // namespace RType::Editor
