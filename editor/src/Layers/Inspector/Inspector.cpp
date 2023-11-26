#include "Inspector.hpp"

namespace RType::Editor
{
    void Inspector::OnAttach() {}
    void Inspector::OnDetach() {}
    void Inspector::OnUpdate() {}
    void Inspector::OnRender()
    {
        ImGui::Begin("Inspector");
        ImGui::End();
    }
} // namespace RType::Editor
