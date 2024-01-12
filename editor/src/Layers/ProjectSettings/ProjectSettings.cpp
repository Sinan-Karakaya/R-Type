/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** ProjectSettings
*/

#include "ProjectSettings.hpp"

namespace RType::Editor
{
    void ProjectSettings::OnAttach() {}

    void ProjectSettings::OnDetach() {}

    void ProjectSettings::OnUpdate() {}

    void ProjectSettings::OnRender()
    {
        ImGui::Begin("Project Settings");
        ImGui::Text("Project Name: %s", g_projectInfos.name.c_str());
        ImGui::Text("Project Path: %s", g_projectInfos.path.c_str());
        ImGui::Text("Start Scene Path: %s", g_projectInfos.startScenePath.c_str());
        ImGui::Separator();
        ImGui::Checkbox("Is Multiplayer game", &g_projectInfos.isMultiplayer);
        ImGui::Separator();
        ImGui::Text("Systems: ");
        for (auto &system : m_registry.GetSystems()) {
            ImGui::Checkbox(system.second->GetName().c_str(), &system.second->enabled);
        }
        ImGui::Separator();
        if (ImGui::Button("Save config")) {
            json j;
            j["name"] = g_projectInfos.name;
            j["startScene"] = g_projectInfos.startScenePath;
            j["runtimeVersion"] = RTYPE_VERSION;
            j["isMultiplayer"] = g_projectInfos.isMultiplayer;
            j["disabledSystems"] = json::array();
            for (auto &system : m_registry.GetSystems()) {
                if (!system.second->enabled)
                    j["disabledSystems"].push_back(system.second->GetName());
            }
            std::fstream file(g_projectInfos.path + "/project.json", std::ios::out);
            if (!file.is_open()) {
                EDITOR_LOG_ERROR("Failed to save project.json");
                exit(84);
            }
            file << j.dump(4);
            file.close();
        }
        ImGui::End();
    }
} // namespace RType::Editor
