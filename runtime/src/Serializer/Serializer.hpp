/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Serializer
*/

#pragma once

#include <nlohmann/json.hpp>

#include "RType.hpp"
#include "Runtime.hpp"

namespace RType::Runtime
{
    using json = nlohmann::json;

    class Runtime;

    class Serializer
    {
    public:
        Serializer() = delete;

        /**
         * @brief Loads a scene from the specified path into the runtime.
         *
         * This function loads a scene from the given path and populates the runtime
         * with the entities and components defined in the scene file.
         *
         * @param path The path to the scene file.
         * @param runtime The runtime object to populate with the scene data.
         * @return True if the scene was successfully loaded, false otherwise.
         */
        static bool loadScene(const std::string &path, RType::Runtime::Runtime &runtime);
        /**
         * Saves the scene to a file.
         *
         * @param path The path to the file where the scene will be saved.
         * @param runtime The runtime object containing the scene to be saved.
         * @return True if the scene was successfully saved, false otherwise.
         */
        static bool saveScene(const std::string &path, RType::Runtime::Runtime &runtime);

        /**
         * Saves the specified entity as a prefab in the runtime.
         *
         * @param runtime The runtime instance.
         * @param entity The entity to be saved as a prefab.
         * @return True if the prefab was successfully saved, false otherwise.
         */
        static bool savePrefab(RType::Runtime::Runtime &runtime, ECS::Entity entity);
        /**
         * @brief Loads a prefab from the specified path.
         *
         * @param runtime The runtime object.
         * @param path The path to the prefab.
         * @return The loaded entity.
         */
        static ECS::Entity loadPrefab(RType::Runtime::Runtime &runtime, const std::string &path);

        /**
         * @brief Update an entity with a json object
         * 
         * @param runtime The runtime object to get entity components
         * @param entity The entity to update
         * @param j The json object to update entity
         */
        static void updateEntity(RType::Runtime::IRuntime &runtime, ECS::Entity entity, const json &j);

        /**
         * @brief Save an entity in a json object
         * 
         * @param runtime The runtime object to get entity components
         * @param entity The entity to save
         * @param j The json object to save entity
         */
        static void saveEntity(RType::Runtime::Runtime &runtime, ECS::Entity entity, json &j);

    private:
        /**
         * @brief Loads entities from a JSON object into the runtime.
         *
         * This function takes a JSON object and a runtime object as parameters.
         * It loads the entities described in the JSON object into the runtime.
         *
         * @param j The JSON object containing the entities.
         * @param runtime The runtime object to load the entities into.
         */
        static void f_loadEntities(json &j, RType::Runtime::Runtime &runtime);
        /**
         * @brief Saves the entities from the runtime into a JSON object.
         *
         * @param j The JSON object to save the entities into.
         * @param runtime The runtime object containing the entities.
         */
        static void f_saveEntities(json &j, RType::Runtime::Runtime &runtime);
    };
} // namespace RType::Runtime
