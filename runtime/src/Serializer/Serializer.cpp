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
        // TODO clear runtime
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

    void Serializer::f_loadEntities(json &j, Runtime &runtime)
    {
        for (auto &entity : j["entities"]) {
            auto e = runtime.GetRegistry().CreateEntity();
            for (auto &component : entity["components"]) {
                if (component["type"] == "Transform") {
                    runtime.GetRegistry().AddComponent(e, ECS::Components::Transform());
                    ECS::Components::Transform transform = component;
                    runtime.GetRegistry().GetComponent<ECS::Components::Transform>(e) = transform;
                }
                if (component["type"] == "RigidBody") {
                    runtime.GetRegistry().AddComponent(e, ECS::Components::RigidBody());
                    ECS::Components::RigidBody rb = component;
                    runtime.GetRegistry().GetComponent<ECS::Components::RigidBody>(e) = rb;
                }
                if (component["type"] == "Gravity") {
                    runtime.GetRegistry().AddComponent(e, ECS::Components::Gravity());
                    ECS::Components::Gravity gravity = component;
                    runtime.GetRegistry().GetComponent<ECS::Components::Gravity>(e) = gravity;
                }
                if (component["type"] == "Script") {
                    runtime.GetRegistry().AddComponent(e, ECS::Components::Script());
                    ECS::Components::Script script = component;
                    runtime.GetRegistry().GetComponent<ECS::Components::Script>(e) = script;
                }
                if (component["type"] == "Drawable") {
                    runtime.GetRegistry().AddComponent(e, ECS::Components::Drawable {
                                                              .sprite = sf::Sprite(), .texture = sf::Texture()});
                    ECS::Components::Drawable drawable = component;
                    runtime.GetRegistry().GetComponent<ECS::Components::Drawable>(e) = drawable;
                }
            }
        }
    }

    void Serializer::f_saveEntities(json &j, Runtime &runtime)
    {
        for (auto &entity : runtime.GetEntities()) {
            json e;
            e["components"] = json::array();

            try {
                auto &transform =
                    runtime.GetRegistry().GetComponent<ECS::Components::Transform>(entity);
                json t;
                t = transform;
                e["components"].push_back(t);
            } catch (const std::exception &e) {
            }
            try {
                auto &rb = runtime.GetRegistry().GetComponent<ECS::Components::RigidBody>(entity);
                json r;
                r = rb;
                e["components"].push_back(r);
            } catch (const std::exception &e) {
            }
            try {
                auto &gravity = runtime.GetRegistry().GetComponent<ECS::Components::Gravity>(entity);
                json g;
                g = gravity;
                e["components"].push_back(g);
            } catch (const std::exception &e) {
            }
            try {
                auto &script = runtime.GetRegistry().GetComponent<ECS::Components::Script>(entity);
                json s;
                s = script;
                e["components"].push_back(s);
            } catch (const std::exception &e) {
            }
            try {
                auto &drawable = runtime.GetRegistry().GetComponent<ECS::Components::Drawable>(entity);
                json d;
                d = drawable;
                e["components"].push_back(d);
            } catch (const std::exception &e) {
            }
            j["entities"].push_back(e);
        }
    }

} // namespace RType::Runtime
