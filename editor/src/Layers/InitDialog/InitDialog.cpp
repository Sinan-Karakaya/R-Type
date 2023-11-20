#include "InitDialog.hpp"

namespace RType::Editor {
    void RType::Editor::InitDialog::OnAttach()
    {
        NFD_Init();
    }

    void InitDialog::OnDetach()
    {
        if (m_path)
            NFD_FreePathN(m_path);
        NFD_Quit();
    }
  
    void InitDialog::OnUpdate()
    {

    }
  
    void InitDialog::OnRender()
    {
        ImGui::Begin("Begin project");
        ImGui::Checkbox("Create a project", &m_create);
        if (m_create) {
            ImGui::Text("Project name:");
            ImGui::SameLine();
            ImGui::InputText("##project_name", m_projectName, IM_ARRAYSIZE(m_projectName));
        }
        if (ImGui::Button("Pick a path")) {
            f_openDialog();    
        }
        ImGui::End();
    }

    void InitDialog::f_openDialog()
    {
        nfdresult_t res = NFD_PickFolderN(&m_path, (nfdnchar_t *)".");

        // This is dumb i know but it is needed if we want to manipulate the result
        std::wstring tmp((wchar_t *)m_path);
        std::string path(tmp.begin(), tmp.end());

        if (res == NFD_OKAY) {
            g_projectInfos.path = path;
            g_projectInfos.shouldLoad = true;
            g_projectInfos.shouldCreate = m_create;
        } else if (res == NFD_CANCEL) {
            EDITOR_LOG_WARN("User pressed cancel.");
        } else {
            EDITOR_LOG_ERROR("Error: {0}", NFD_GetError());
        }
    }
} // namespace RType::Editor
