#include "Viewport.hpp"

namespace RType::Editor
{
    void Viewport::OnAttach()
    {
        m_libHandle = RType::Utils::Modules::LoadSharedLibrary("runtime");
        // ASSERT(m_libHandle, "Failed to load runtime library")

        RType::Runtime::IRuntime *(*runtimeEntry)() =
            (RType::Runtime::IRuntime * (*)()) RType::Utils::Modules::GetFunction(m_libHandle, "RuntimeEntry");
        // ASSERT(runtimeEntry, "Failed to get runtime entry point")

        m_runtime = std::unique_ptr<RType::Runtime::IRuntime>(runtimeEntry());
        m_runtime->Init(1920, 1080);

        m_registry = std::make_unique<Registry>();
        m_registry->registerComponent<RType::ECS::Components::Position>();
        m_registry->registerComponent<RType::ECS::Components::Velocity>();
        m_registry->registerComponent<RType::ECS::Components::Drawable>();
        m_registry->registerComponent<RType::ECS::Components::Controllable>();
    }

    void Viewport::OnDetach()
    {
        m_runtime->Destroy();
        m_runtime.reset();
        ASSERT(RType::Utils::Modules::FreeSharedLibrary(m_libHandle), "Failed to free runtime library")
    }

    void Viewport::OnUpdate()
    {
        m_runtime->Update();
        m_runtime->Render();
    }

    void Viewport::OnRender()
    {
        ImGui::Begin("Viewport");
        ImGui::Image(m_runtime->GetRenderTexture());
        if (ImGui::BeginDragDropTarget()) {
            if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("Asset")) {
                ImVec2 pos = ImGui::GetMousePos();
                ImVec2 winPos = ImGui::GetWindowPos();
                ImVec2 localPos = ImVec2(pos.x - winPos.x, pos.y - winPos.y);
                RTYPE_LOG_INFO("Accepted payload: {} at {} {}", (char *)payload->Data, localPos.x, localPos.y);
            }
            ImGui::EndDragDropTarget();
        }
        ImGui::End();
    }
} // namespace RType::Editor
