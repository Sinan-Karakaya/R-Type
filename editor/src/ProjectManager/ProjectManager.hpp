/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ProjectManager
*/

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
        /**
         * @brief Loads a project.
         *
         * This function is responsible for loading a project.
         * It performs the necessary operations to load the project data
         * and make it available for further processing.
         *
         * @note This function is static and can be called without creating an instance of ProjectManager.
         */
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
            g_projectInfos.startScenePath = j["startScene"];
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

        /**
         * @brief Creates a new project.
         *
         * This function is responsible for creating a new project.
         * It performs the necessary steps to initialize a new project,
         * such as creating the project directory, setting up the necessary files, etc.
         *
         * @note This function is static and can be called without an instance of the ProjectManager class.
         */
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
            j["startScene"] = "assets/scenes/default.json";
            file << std::setw(4) << j << std::endl;

            file.close();
            ProjectManager::LoadProject();
        }

        /**
         * @brief Saves the project using the provided runtime and path.
         *
         * @param runtime The runtime object used to save the project.
         * @param path The path where the project will be saved.
         */
        static void SaveProject(std::unique_ptr<RType::Runtime::IRuntime> &runtime, const char *path)
        {
            if (!(runtime->saveScene(g_projectInfos.path + "/assets/scenes/" + path + ".json")))
                EDITOR_LOG_ERROR("Failed to save scene");
        }

        /**
         * @brief Loads a project into the runtime.
         *
         * This function loads a project into the provided runtime.
         *
         * @param runtime A reference to the runtime object.
         * @param path The path to the project to be loaded.
         */
        static void LoadProject(std::unique_ptr<RType::Runtime::IRuntime> &runtime, const char *path)
        {
            if (!(runtime->loadScene(g_projectInfos.path + "/assets/scenes/" + path + ".json")))
                EDITOR_LOG_ERROR("Failed to load scene");
        }
    };
} // namespace RType::Editor
