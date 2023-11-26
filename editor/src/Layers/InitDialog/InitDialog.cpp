#include "InitDialog.hpp"

namespace RType::Editor
{
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

    void InitDialog::OnUpdate() {}

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
            try {
                f_openDialog();
            } catch (std::exception &e) {
                EDITOR_LOG_ERROR("Error: {0}", e.what());
            }
            // f_openDialog();
        }
        if (m_path) {
            ImGui::SameLine();
            ImGui::Text("%s", g_projectInfos.path.c_str());
        }
        if (ImGui::Button(m_create ? "Create" : "Load")) {
            if (m_create && !m_projectName && m_projectName[0] == '\0') {
                EDITOR_LOG_WARN("Project name is empty");
            } else if (m_path == nullptr) {
                EDITOR_LOG_WARN("Path is empty");
            } else {
                g_projectInfos.shouldLoad = true;
                g_projectInfos.shouldCreate = m_create;
            }
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
        } else if (res == NFD_CANCEL) {
            EDITOR_LOG_WARN("User pressed cancel.");
        } else {
            EDITOR_LOG_ERROR("Error: {0}", NFD_GetError());
        }
    }
} // namespace RType::Editor
