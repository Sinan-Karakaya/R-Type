/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Runtime
*/

#include "Runtime.hpp"

extern "C" RTYPE_EXPORT RType::Runtime::IRuntime *RuntimeEntry()
{
    return new RType::Runtime::Runtime();
}

extern "C" RTYPE_EXPORT void RuntimeDestroy(RType::Runtime::IRuntime *runtime)
{
    delete runtime;
}

namespace RType::Runtime
{

    void Runtime::Init(int width, int height, bool isServer)
    {
        m_isServer = isServer;
        m_camera.setSize(width, height);
        m_renderTexture.create(width, height);
        m_renderTexture.setSmooth(true);
        m_renderTexture.setView(m_camera);

        m_registry.Init();
        m_registry.RegisterComponent<RType::Runtime::ECS::Components::Transform>();
        m_registry.RegisterComponent<RType::Runtime::ECS::Components::RigidBody>();
        m_registry.RegisterComponent<RType::Runtime::ECS::Components::Drawable>();
        m_registry.RegisterComponent<RType::Runtime::ECS::Components::CircleShape>();
        m_registry.RegisterComponent<RType::Runtime::ECS::Components::UIRectangleElement>();
        m_registry.RegisterComponent<RType::Runtime::ECS::Components::Script>();
        m_registry.RegisterComponent<RType::Runtime::ECS::Components::Controllable>();
        m_registry.RegisterComponent<RType::Runtime::ECS::Components::IAControllable>();
        m_registry.RegisterComponent<RType::Runtime::ECS::Components::Tag>();

        InitLua();
        AssetManager::init();
        std::ifstream file("project.json");
        if (file.is_open()) {
            nlohmann::json j;
            file >> j;
            loadScene(j["startScene"]);
            file.close();
        }
    }

    void Runtime::InitLua()
    {
        m_lua.open_libraries(sol::lib::base);

        m_lua.new_usertype<sf::Vector2f>("vector", sol::constructors<sf::Vector2f(float, float)>(), "x",
                                         &sf::Vector2f::x, "y", &sf::Vector2f::y);

#ifndef __APPLE__
        m_lua.new_usertype<RType::Runtime::ECS::Components::Transform>(
            "transform",
            sol::constructors<RType::Runtime::ECS::Components::Transform(sf::Vector2f, sf::Vector2f, sf::Vector2f)>(),
            "position", &RType::Runtime::ECS::Components::Transform::position, "rotation",
            &RType::Runtime::ECS::Components::Transform::rotation, "scale",
            &RType::Runtime::ECS::Components::Transform::scale);
        m_lua.new_usertype<RType::Runtime::ECS::Components::RigidBody>(
            "rigidbody", "velocity", &RType::Runtime::ECS::Components::RigidBody::velocity, "acceleration",
            &RType::Runtime::ECS::Components::RigidBody::acceleration, "mass",
            &RType::Runtime::ECS::Components::RigidBody::mass, "useGravity",
            &RType::Runtime::ECS::Components::RigidBody::useGravity, "isKinematic",
            &RType::Runtime::ECS::Components::RigidBody::isKinematic);
        m_lua.new_usertype<RType::Runtime::ECS::Components::Tag>(
            "tag", sol::constructors<RType::Runtime::ECS::Components::Tag()>(), "tag",
            &RType::Runtime::ECS::Components::Tag::tag);
#endif

        // TODO: implement all getters
        m_lua.set_function("getComponentTransform",
                           [&](RType::Runtime::ECS::Entity e) -> RType::Runtime::ECS::Components::Transform & {
                               return m_registry.GetComponent<RType::Runtime::ECS::Components::Transform>(e);
                           });
        m_lua.set_function("getComponentRigidBody",
                           [&](RType::Runtime::ECS::Entity e) -> RType::Runtime::ECS::Components::RigidBody & {
                               return m_registry.GetComponent<RType::Runtime::ECS::Components::RigidBody>(e);
                           });
        m_lua.set_function("getComponentTag", [&](RType::Runtime::ECS::Entity e) -> const char * {
            return m_registry.GetComponent<RType::Runtime::ECS::Components::Tag>(e).tag;
        });
        m_lua.set_function("getCameraSize",
                           [&]() -> sf::Vector2f { return static_cast<sf::Vector2f>(m_renderTexture.getSize()); });
        m_lua.set_function("getInput", [&](RType::Runtime::ECS::Entity e, const char *str) -> bool {
            try {
                auto &controllable = m_registry.GetComponent<RType::Runtime::ECS::Components::Controllable>(e);
                return sf::Keyboard::isKeyPressed(controllable.inputs[std::string(str)]);
            } catch (std::exception &e) {
                return false;
            }
        });
        m_lua.set_function("destroyEntity", [&](RType::Runtime::ECS::Entity e) -> void { this->RemoveEntity(e); });
        m_lua.set_function("addPrefab",
                           [&](const char *path) -> RType::Runtime::ECS::Entity { return this->loadPrefab(path); });
    }

    void Runtime::Destroy()
    {
        for (const auto &entity : m_entities)
            this->RemoveEntity(entity);
        m_renderTexture.clear();
        m_lua = sol::state();
    }

    void Runtime::Update(sf::Event &event)
    {
        if (event.type == sf::Event::Resized)
            HandleResizeEvent(event);

        for (const auto &entity : m_entities) {
            f_updateSprites(entity);
            f_updateTransforms(entity);
            f_updateScripts(entity);
        }
    }

    void Runtime::Update()
    {
        for (const auto &entity : m_entities) {
            f_updateScripts(entity);
        }
    }

    void Runtime::Render()
    {
        m_renderTexture.clear(sf::Color::Black);

        for (const auto &entity : m_entities) {
            SKIP_EXCEPTIONS({
                const auto &controllable =
                    m_registry.GetComponent<RType::Runtime::ECS::Components::Controllable>(entity);

                if (!controllable.isActive) {
                    continue;
                }
            })
            SKIP_EXCEPTIONS({
                const auto &iacontrollable =
                    m_registry.GetComponent<RType::Runtime::ECS::Components::IAControllable>(entity);

                if (!iacontrollable.isActive) {
                    continue;
                }
            })
            SKIP_EXCEPTIONS({
                const auto &drawable = m_registry.GetComponent<RType::Runtime::ECS::Components::Drawable>(entity);

                m_renderTexture.draw(drawable.sprite);
            })

            SKIP_EXCEPTIONS({
                const auto &circleShape = m_registry.GetComponent<RType::Runtime::ECS::Components::CircleShape>(entity);

                m_renderTexture.draw(circleShape.circle);
            })

            SKIP_EXCEPTIONS({
                const auto &uiRectangleElement =
                    m_registry.GetComponent<RType::Runtime::ECS::Components::UIRectangleElement>(entity);

                m_renderTexture.draw(uiRectangleElement.rectangle);
                m_renderTexture.draw(uiRectangleElement.text);
            })
        }

        m_renderTexture.display();
    }

    sf::Sprite Runtime::GetRenderTextureSprite()
    {
        const sf::Texture &texture = m_renderTexture.getTexture();
        sf::Sprite sprite(texture);
        return sprite;
    }

    RType::Runtime::ECS::Entity Runtime::AddEntity()
    {
        auto entity = m_registry.CreateEntity();
        m_entities.push_back(entity);
        return entity;
    }

    void Runtime::RemoveEntity(RType::Runtime::ECS::Entity entity)
    {
        m_registry.DestroyEntity(entity);
        m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), entity), m_entities.end());
    }

    void Runtime::HandleResizeEvent(sf::Event event)
    {
        m_renderTexture.create(event.size.width, event.size.height);
    }

    void Runtime::HandleResizeEvent(float x, float y)
    {
        m_renderTexture.create(x, y);
    }

    bool Runtime::loadScene(const std::string &path)
    {
        return RType::Runtime::Serializer::loadScene(path, *this);
    }

    bool Runtime::saveScene(const std::string &path)
    {
        return RType::Runtime::Serializer::saveScene(path, *this);
    }

    bool Runtime::savePrefab(RType::Runtime::ECS::Entity entity)
    {
        return Serializer::savePrefab(*this, entity);
    }

    RType::Runtime::ECS::Entity Runtime::loadPrefab(const std::string &path)
    {
        return Serializer::loadPrefab(*this, path);
    }

    void Runtime::f_updateTransforms(RType::Runtime::ECS::Entity entity)
    {
        SKIP_EXCEPTIONS({
            const auto &transform = m_registry.GetComponent<RType::Runtime::ECS::Components::Transform>(entity);
            auto &drawable = m_registry.GetComponent<RType::Runtime::ECS::Components::Drawable>(entity);
            drawable.sprite.setPosition(transform.position);
            drawable.sprite.setRotation(transform.rotation.x);
            drawable.sprite.setScale(transform.scale);
        })
        SKIP_EXCEPTIONS({
            const auto &transform = m_registry.GetComponent<RType::Runtime::ECS::Components::Transform>(entity);
            auto &circle = m_registry.GetComponent<RType::Runtime::ECS::Components::CircleShape>(entity);
            circle.circle.setOrigin(circle.circle.getLocalBounds().width / 2,
                                    circle.circle.getLocalBounds().height / 2);
            circle.circle.setPosition(transform.position);
            circle.circle.setRotation(transform.rotation.x);
            circle.circle.setScale(transform.scale);
        })
    }

    void Runtime::f_updateSprites(RType::Runtime::ECS::Entity entity)
    {
        SKIP_EXCEPTIONS({
            auto &drawable = m_registry.GetComponent<RType::Runtime::ECS::Components::Drawable>(entity);
            const std::string drawableFullPath = m_projectPath + "/assets/sprites/" + drawable.path;
            if (!drawable.isLoaded && std::filesystem::exists(drawableFullPath) && drawableFullPath.ends_with(".png")) {
                drawable.texture = AssetManager::getTexture(drawableFullPath);
                drawable.sprite.setTexture(drawable.texture);
                drawable.sprite.setOrigin(drawable.sprite.getLocalBounds().width / 2,
                                          drawable.sprite.getLocalBounds().height / 2);
                drawable.isLoaded = true;
            }
            // TODO: handle rect + animations but in other if statement
        })
    }

    void Runtime::f_updateColliders(RType::Runtime::ECS::Entity entity, const std::string &path)
    {
        auto &drawable = m_registry.GetComponent<RType::Runtime::ECS::Components::Drawable>(entity);
        if (drawable.isCollidable) {
            for (auto &e : m_entities) {
                if (e == entity) {
                    continue;
                }
                auto &drawable2 = m_registry.GetComponent<RType::Runtime::ECS::Components::Drawable>(e);
                if (drawable2.isCollidable) {
                    if (drawable.sprite.getGlobalBounds().intersects(drawable2.sprite.getGlobalBounds())) {
                        sol::function f = m_lua["onCollision"];
                        sol::protected_function_result res = f(entity, e);
                        if (!res.valid()) {
                            sol::error err = res;
                            RTYPE_LOG_ERROR("{0}: {1}", path, err.what());
                        }
                    }
                }
            }
        }

        auto &circle = m_registry.GetComponent<RType::Runtime::ECS::Components::CircleShape>(entity);
        if (circle.isCollidable) {
            for (auto &e : m_entities) {
                if (e == entity) {
                    continue;
                }
                auto &circle2 = m_registry.GetComponent<RType::Runtime::ECS::Components::CircleShape>(e);
                if (circle2.isCollidable) {
                    if (drawable.sprite.getGlobalBounds().intersects(circle2.circle.getGlobalBounds())) {
                        sol::function f = m_lua["onCollision"];
                        sol::protected_function_result res = f(entity, e);
                        if (!res.valid()) {
                            sol::error err = res;
                            RTYPE_LOG_ERROR("{0}: {1}", path, err.what());
                        }
                    }
                }
            }
        }
    }

    void Runtime::f_updateScripts(RType::Runtime::ECS::Entity entity)
    {
        SKIP_EXCEPTIONS({
            auto &controllable = m_registry.GetComponent<RType::Runtime::ECS::Components::Controllable>(entity);
            if (!controllable.isActive)
                return;
        })
        SKIP_EXCEPTIONS({
            auto &script = m_registry.GetComponent<RType::Runtime::ECS::Components::Script>(entity);

            for (int i = 0; i < 6; i++) {
                std::string currentPath = script.paths[i];
                if (currentPath.empty() || !currentPath.ends_with(".lua")) {
                    continue;
                }
                std::string fullPath = m_projectPath + "/assets/scripts/" + currentPath;
                if (!std::filesystem::exists(fullPath)) {
                    continue;
                }

                std::string script_content = AssetManager::getScript(fullPath);
                m_lua.script(script_content);
                if (m_isServer) {
                    sol::function f = m_lua["updateServer"];
                    sol::protected_function_result res = f(entity);
                    if (!res.valid()) {
                        sol::error err = res;
                        RTYPE_LOG_ERROR("{0}: {1}", script.paths[i], err.what());
                    }
                }
                sol::function f = m_lua["update"];
                sol::protected_function_result res = f(entity);
                if (!res.valid()) {
                    sol::error err = res;
                    RTYPE_LOG_ERROR("{0}: {1}", script.paths[i], err.what());
                }

                f_updateColliders(entity, script.paths[i]);
            }
        })
    }

} // namespace RType::Runtime
