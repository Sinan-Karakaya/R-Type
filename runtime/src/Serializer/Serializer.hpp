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

        static bool loadScene(const std::string &path, RType::Runtime::Runtime &runtime);
        static bool saveScene(const std::string &path, RType::Runtime::Runtime &runtime);

        static bool savePrefab(RType::Runtime::Runtime &runtime, ECS::Entity entity);
        static ECS::Entity loadPrefab(RType::Runtime::Runtime &runtime, const std::string &path);

    private:
        static void f_loadEntities(json &j, RType::Runtime::Runtime &runtime);
        static void f_saveEntities(json &j, RType::Runtime::Runtime &runtime);
    };
} // namespace RType::Runtime
