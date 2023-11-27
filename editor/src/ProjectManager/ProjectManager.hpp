#pragma once

#include <filesystem>
#include <fstream>

#include <nlohmann/json.hpp>

#include "Editor.hpp"

namespace RType::Editor
{

    using json = nlohmann::json;

    class ProjectManager
    {
    public:
        static void LoadProject()
        {
            std::fstream file(g_projectInfos.path + "/project.json", std::ios::in);
            json j;

            if (!file.is_open()) {
                EDITOR_LOG_ERROR("Failed to open project.json");
                exit(84);
            }
            
            file >> j;
            file.close();

            g_projectInfos.name = j["name"];
            const std::string version = j["runtimeVersion"].get<std::string>();
            if (version != std::string(RTYPE_VERSION)) {
                EDITOR_LOG_CRITICAL("Project version is not compatible with the editor version");
                EDITOR_LOG_CRITICAL("Project version expected: {}", RTYPE_VERSION);
                EDITOR_LOG_CRITICAL("Project version found: {}", version);
                exit(84);
            }

            g_projectInfos.shouldLoad = false;
            g_projectInfos.shouldCreate = false;
        }

        static void CreateProject()
        {
            std::filesystem::create_directory(g_projectInfos.path);
            std::filesystem::create_directory(g_projectInfos.path + "/assets");
            std::filesystem::create_directory(g_projectInfos.path + "/assets/sprites");
            std::filesystem::create_directory(g_projectInfos.path + "/assets/sounds");
            std::filesystem::create_directory(g_projectInfos.path + "/assets/fonts");
            std::filesystem::create_directory(g_projectInfos.path + "/assets/scripts");
            std::filesystem::create_directory(g_projectInfos.path + "/assets/scenes");
            std::filesystem::create_directory(g_projectInfos.path + "/assets/prefabs");

            std::fstream file(g_projectInfos.path + "/project.json", std::ios::out);
            json j;

            j["name"] = g_projectInfos.name;
            j["runtimeVersion"] = RTYPE_VERSION;
            file << std::setw(4) << j << std::endl;

            file.close();
            ProjectManager::LoadProject();
        }

        static void SaveProject() {}
    };
} // namespace RType::Editor
