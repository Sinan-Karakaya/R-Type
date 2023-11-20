#pragma once

#include <fstream>
#include <nlohmann/json.hpp>

#include "Editor.hpp"

namespace RType::Editor {

    using json = nlohmann::json;

    class ProjectManager {
    public:
        static void LoadProject()
        {
            std::fstream file(g_projectInfos.path + "/project.json", std::ios::in);
            json j;

            file >> j;
            g_projectInfos.name = j["name"];
            file.close();
        }

        static void CreateProject()
        {
            std::fstream file(g_projectInfos.path + "/project.json", std::ios::out);
            json j;

            j["name"] = g_projectInfos.name;
            j["runtimeVersion"] = RTYPE_VERSION_MAJOR + "." + RTYPE_VERSION_MINOR;
            file << j;

            file.close();
            ProjectManager::LoadProject();
        }
        
        static void SaveProject() {}
    };
}