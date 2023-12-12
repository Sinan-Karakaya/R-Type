#include "Viewport.hpp"

namespace RType::Editor
{
    void Viewport::OnAttach()
    {
    }

    void Viewport::OnDetach()
    {
        m_runtime.Destroy();
    }

    void Viewport::OnUpdate()
    {
        m_runtime.Update(m_event);
        if (m_contentRegionSize.x > 0 && m_contentRegionSize.y > 0)
            m_runtime.HandleResizeEvent(m_contentRegionSize.x, m_contentRegionSize.y);
        m_runtime.Render();
    }

    void Viewport::OnRender()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::Begin("Viewport");
        ImGui::Image(m_runtime.GetRenderTexture());
        if (ImGui::BeginDragDropTarget()) {
            if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("Asset")) {
                ImVec2 pos = ImGui::GetMousePos();
                ImVec2 winPos = ImGui::GetWindowPos();
                ImVec2 localPos = ImVec2(pos.x - winPos.x, pos.y - winPos.y);
                RTYPE_LOG_INFO("Accepted payload: {} at {} {}", (char *)payload->Data, localPos.x, localPos.y);
            }
            ImGui::EndDragDropTarget();
        }
        ImVec2 contentRegion = ImGui::GetContentRegionAvail();
        m_contentRegionSize = contentRegion;

        ImGui::End();
        ImGui::PopStyleVar();
    }
} // namespace RType::Editor
