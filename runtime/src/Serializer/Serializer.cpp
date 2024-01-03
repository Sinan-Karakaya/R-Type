/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Serializer
*/

#include "Serializer.hpp"

namespace RType::Runtime
{

    bool Serializer::loadScene(const std::string &path, Runtime &runtime)
    {
        runtime.Destroy();
        runtime.Init();

        std::ifstream file(path);
        if (!file.is_open()) {
            RUNTIME_LOG_ERROR("Failed to open file: " + path);
            return false;
        }

        json j;
        file >> j;
        file.close();

        f_loadEntities(j, runtime);

        for (auto &entity : runtime.GetEntities()) {
            SKIP_EXCEPTIONS({
                auto &controllable = runtime.GetRegistry().GetComponent<ECS::Components::Controllable>(entity);
                controllable.isActive = false;
            })
        }

        return true;
    }

    bool Serializer::saveScene(const std::string &path, Runtime &runtime)
    {
        std::ofstream file(path);
        if (!file.is_open()) {
            RUNTIME_LOG_ERROR("Failed to open file: " + path);
            return false;
        }

        json j;
        j["entities"] = json::array();
        f_saveEntities(j, runtime);
        file << j;
        file.close();

        return true;
    }

    void Serializer::updateEntity(RType::Runtime::IRuntime &runtime, ECS::Entity entity, const json &j)
    {
        for (auto &component : j["components"]) {
            if (component["type"] == "Transform") {
                auto &transform = runtime.GetRegistry().GetComponent<ECS::Components::Transform>(entity);
                transform = component;
            }
            if (component["type"] == "RigidBody") {
                auto &rb = runtime.GetRegistry().GetComponent<ECS::Components::RigidBody>(entity);
                rb = component;
            }
            if (component["type"] == "Drawable") {
                auto &drawable = runtime.GetRegistry().GetComponent<ECS::Components::Drawable>(entity);
                drawable = component;
            }
            if (component["type"] == "CircleShape") {
                auto &circle = runtime.GetRegistry().GetComponent<ECS::Components::CircleShape>(entity);
                circle = component;
            }
            if (component["type"] == "Script") {
                auto &script = runtime.GetRegistry().GetComponent<ECS::Components::Script>(entity);
                script = component;
            }
            if (component["type"] == "Controllable") {
                auto &controllable = runtime.GetRegistry().GetComponent<ECS::Components::Controllable>(entity);
                controllable = component;
            }
            if (component["type"] == "IAControllable") {
                auto &ia = runtime.GetRegistry().GetComponent<ECS::Components::IAControllable>(entity);
                ia = component;
            }
            if (component["type"] == "Tag") {
                auto &tag = runtime.GetRegistry().GetComponent<ECS::Components::Tag>(entity);
                tag = component;
            }
            if (component["type"] == "CollisionBox") {
                auto &collisionBox = runtime.GetRegistry().GetComponent<ECS::Components::CollisionBox>(entity);
                collisionBox = component;
            }
        }
    }

    void Serializer::f_loadEntities(json &j, Runtime &runtime)
    {
        for (auto &entity : j["entities"]) {
            auto e = runtime.AddEntity();
            for (auto &component : entity["components"]) {
                f_loadComponent<ECS::Components::Transform>(component, e, runtime, "Transform");
                f_loadComponent<ECS::Components::RigidBody>(component, e, runtime, "RigidBody");
                f_loadComponent<ECS::Components::Drawable>(component, e, runtime, "Drawable");
                f_loadComponent<ECS::Components::CircleShape>(component, e, runtime, "CircleShape");
                f_loadComponent<ECS::Components::Script>(component, e, runtime, "Script");
                f_loadComponent<ECS::Components::Controllable>(component, e, runtime, "Controllable");
                f_loadComponent<ECS::Components::IAControllable>(component, e, runtime, "IAControllable");
                f_loadComponent<ECS::Components::Tag>(component, e, runtime, "Tag");
                f_loadComponent<ECS::Components::CollisionBox>(component, e, runtime, "CollisionBox");
            }
        }
    }

    void Serializer::saveEntity(RType::Runtime::Runtime &runtime, ECS::Entity entity, json &j)
    {
        j["components"] = json::array();

        f_saveComponent<ECS::Components::Transform>(j["components"], entity, runtime);
        f_saveComponent<ECS::Components::RigidBody>(j["components"], entity, runtime);
        f_saveComponent<ECS::Components::Drawable>(j["components"], entity, runtime);
        f_saveComponent<ECS::Components::CircleShape>(j["components"], entity, runtime);
        f_saveComponent<ECS::Components::Script>(j["components"], entity, runtime);
        f_saveComponent<ECS::Components::Controllable>(j["components"], entity, runtime);
        f_saveComponent<ECS::Components::IAControllable>(j["components"], entity, runtime);
        f_saveComponent<ECS::Components::Tag>(j["components"], entity, runtime);
        f_saveComponent<ECS::Components::CollisionBox>(j["components"], entity, runtime);
    }

    void Serializer::f_saveEntities(json &j, Runtime &runtime)
    {
        for (auto &entity : runtime.GetEntities()) {
            json e;
            saveEntity(runtime, entity, e);
            e["components"] = json::array();
            j["entities"].push_back(e);
        }
    }

    bool Serializer::savePrefab(Runtime &runtime, ECS::Entity entity)
    {
        try {
            auto &tag = runtime.GetRegistry().GetComponent<ECS::Components::Tag>(entity);
            std::ofstream file(runtime.getProjectPath() + "/assets/prefabs/" + std::string(tag.tag) + ".prefab");
            json j;

            j["components"] = json::array();

            f_saveComponent<ECS::Components::Transform>(j["components"], entity, runtime);
            f_saveComponent<ECS::Components::RigidBody>(j["components"], entity, runtime);
            f_saveComponent<ECS::Components::Drawable>(j["components"], entity, runtime);
            f_saveComponent<ECS::Components::CircleShape>(j["components"], entity, runtime);
            f_saveComponent<ECS::Components::Script>(j["components"], entity, runtime);
            f_saveComponent<ECS::Components::Controllable>(j["components"], entity, runtime);
            f_saveComponent<ECS::Components::IAControllable>(j["components"], entity, runtime);
            f_saveComponent<ECS::Components::Tag>(j["components"], entity, runtime);
            f_saveComponent<ECS::Components::CollisionBox>(j["components"], entity, runtime);
            file << j;
            file.close();
            return true;
        } catch (std::exception &e) {
            RUNTIME_LOG_ERROR("Failed to save prefab: {0}", e.what());
            return false;
        }
    }

    ECS::Entity Serializer::loadPrefab(RType::Runtime::Runtime &runtime, const std::string &path)
    {
        try {
            std::ifstream file(runtime.getProjectPath() + "/assets/prefabs/" + path + ".prefab");
            if (!file.is_open()) {
                RUNTIME_LOG_ERROR("Failed to open file: " + path);
                return 0;
            }

            json j;
            file >> j;
            file.close();

            auto e = runtime.AddEntity();
            for (auto &component : j["components"]) {
                f_loadComponent<ECS::Components::Transform>(component, e, runtime, "Transform");
                f_loadComponent<ECS::Components::RigidBody>(component, e, runtime, "RigidBody");
                f_loadComponent<ECS::Components::Drawable>(component, e, runtime, "Drawable");
                f_loadComponent<ECS::Components::CircleShape>(component, e, runtime, "CircleShape");
                f_loadComponent<ECS::Components::Script>(component, e, runtime, "Script");
                f_loadComponent<ECS::Components::Controllable>(component, e, runtime, "Controllable");
                f_loadComponent<ECS::Components::IAControllable>(component, e, runtime, "IAControllable");
                f_loadComponent<ECS::Components::Tag>(component, e, runtime, "Tag");
                f_loadComponent<ECS::Components::CollisionBox>(component, e, runtime, "CollisionBox");
            }
            return e;
        } catch (std::exception &e) {
            RUNTIME_LOG_ERROR("Failed to load prefab: {0}", e.what());
            return -1;
        }
    }

    template <typename T>
    void Serializer::f_loadComponent(json &component, ECS::Entity entity, RType::Runtime::Runtime &runtime,
                                     const std::string &type)
    {
        if (component["type"] == type) {
            runtime.GetRegistry().AddComponent<T>(entity, component);
            auto &t = runtime.GetRegistry().GetComponent<T>(entity);
            t = component;
        }
    }

    template <typename T>
    void Serializer::f_saveComponent(json &component, ECS::Entity entity, RType::Runtime::Runtime &runtime)
    {
        SKIP_EXCEPTIONS({
            auto &t = runtime.GetRegistry().GetComponent<T>(entity);
            json j;
            j = t;
            component.push_back(j);
        })
    }

} // namespace RType::Runtime
