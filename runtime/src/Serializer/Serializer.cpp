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
            auto e = runtime.AddEntity();
            for (auto &component : entity["components"]) {
                if (component["type"] == "Transform") {
                    runtime.GetRegistry().AddComponent<ECS::Components::Transform>(e, ECS::Components::Transform {});
                    auto &transform = runtime.GetRegistry().GetComponent<ECS::Components::Transform>(e);
                    transform = component;
                }
                if (component["type"] == "Gravity")
                    runtime.GetRegistry().AddComponent<ECS::Components::Gravity>(e, component);
                if (component["type"] == "RigidBody")
                    runtime.GetRegistry().AddComponent<ECS::Components::RigidBody>(e, component);
                if (component["type"] == "Drawable") {
                    runtime.GetRegistry().AddComponent<ECS::Components::Drawable>(e, ECS::Components::Drawable {});
                    auto &drawable = runtime.GetRegistry().GetComponent<ECS::Components::Drawable>(e);
                    drawable = component;
                }
                if (component["type"] == "CircleShape")
                    runtime.GetRegistry().AddComponent<ECS::Components::CircleShape>(e, component);
                if (component["type"] == "Script")
                    runtime.GetRegistry().AddComponent<ECS::Components::Script>(e, component);
                if (component["type"] == "Controllable")
                    runtime.GetRegistry().AddComponent<ECS::Components::Controllable>(e, component);
                if (component["type"] == "IAControllable")
                    runtime.GetRegistry().AddComponent<ECS::Components::IAControllable>(e, component);
                if (component["type"] == "Tag")
                    runtime.GetRegistry().AddComponent<ECS::Components::Tag>(e, component);
            }
        }
    }

    void Serializer::f_saveEntities(json &j, Runtime &runtime)
    {
        for (auto &entity : runtime.GetEntities()) {
            json e;
            e["components"] = json::array();

            SKIP_EXCEPTIONS({
                auto &transform = runtime.GetRegistry().GetComponent<ECS::Components::Transform>(entity);
                json t;
                t = transform;
                e["components"].push_back(t);
            })
            SKIP_EXCEPTIONS({
                auto &rb = runtime.GetRegistry().GetComponent<ECS::Components::RigidBody>(entity);
                json r;
                r = rb;
                e["components"].push_back(r);
            })
            SKIP_EXCEPTIONS({
                auto &gravity = runtime.GetRegistry().GetComponent<ECS::Components::Gravity>(entity);
                json g;
                g = gravity;
                e["components"].push_back(g);
            })
            SKIP_EXCEPTIONS({
                auto &script = runtime.GetRegistry().GetComponent<ECS::Components::Script>(entity);
                json s;
                s = script;
                e["components"].push_back(s);
            })
            SKIP_EXCEPTIONS({
                auto &drawable = runtime.GetRegistry().GetComponent<ECS::Components::Drawable>(entity);
                json d;
                d = drawable;
                e["components"].push_back(d);
            })
            SKIP_EXCEPTIONS({
                auto &circle = runtime.GetRegistry().GetComponent<ECS::Components::CircleShape>(entity);
                json c;
                c = circle;
                e["components"].push_back(c);
            })
            SKIP_EXCEPTIONS({
                auto &controllable = runtime.GetRegistry().GetComponent<ECS::Components::Controllable>(entity);
                json c;
                c = controllable;
                e["components"].push_back(c);
            })
            SKIP_EXCEPTIONS({
<<<<<<< HEAD
                auto &iaControllable = runtime.GetRegistry().GetComponent<ECS::Components::IAControllable>(entity);
                json c;
                c = iaControllable;
=======
                auto &tag = runtime.GetRegistry().GetComponent<ECS::Components::Tag>(entity);
                json c;
                c = tag;
>>>>>>> origin/dev
                e["components"].push_back(c);
            })
            j["entities"].push_back(e);
        }
    }

} // namespace RType::Runtime
