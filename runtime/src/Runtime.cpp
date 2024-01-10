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

    void Runtime::Init(int width, int height, const std::string &projectPath, bool isServer)
    {
        RType::Utils::CrashUtils::setupCatcher();
        INIT_FILE_LOG

        if (!projectPath.empty())
            m_projectPath = projectPath;
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
        m_registry.RegisterComponent<RType::Runtime::ECS::Components::CollisionBox>();

        InitLua();
        AssetManager::init();
    }

    void Runtime::InitLua()
    {
        m_lua.open_libraries(sol::lib::base, sol::lib::math);

        // Create tables env for each script file to able lua to store variables
        std::string folderPath = "./assets/scripts/";
        for (const auto &entry : std::filesystem::directory_iterator(folderPath)) {
            if (entry.path().extension() != ".lua")
                continue;
            std::string scriptName = entry.path().filename().string();
            sol::table env = m_lua.create_table();

            scriptName = scriptName.substr(0, scriptName.find_last_of("."));
            m_lua[scriptName] = env;
            // m_lua[scriptName]["test"] = 42;
        }

        m_lua.new_usertype<sf::Vector2f>("vector", sol::constructors<sf::Vector2f(float, float)>(), "x",
                                         &sf::Vector2f::x, "y", &sf::Vector2f::y);
        // Create the user type for sf::FloatRect
        m_lua.new_usertype<sf::FloatRect>("floatRect", sol::constructors<sf::FloatRect(float, float, float, float)>(),
                                          "left", &sf::FloatRect::left, "top", &sf::FloatRect::top, "width",
                                          &sf::FloatRect::width, "height", &sf::FloatRect::height);

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

        m_lua.new_usertype<RType::Runtime::ECS::Components::Drawable>(
            "drawable", "floatRect", &RType::Runtime::ECS::Components::Drawable::rect, "frameCount",
            &RType::Runtime::ECS::Components::Drawable::frameCount, "frameDuration",
            &RType::Runtime::ECS::Components::Drawable::frameDuration, "leftDecal",
            &RType::Runtime::ECS::Components::Drawable::leftDecal, "startPosition",
            &RType::Runtime::ECS::Components::Drawable::startPosition, "isAnimated",
            &RType::Runtime::ECS::Components::Drawable::isAnimated, "autoPlay",
            &RType::Runtime::ECS::Components::Drawable::autoPlay, "currentFrame",
            &RType::Runtime::ECS::Components::Drawable::currentFrame);
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
        m_lua.set_function("restartClockAnimation", [&](RType::Runtime::ECS::Entity e) -> void {
            auto &drawable = m_registry.GetComponent<RType::Runtime::ECS::Components::Drawable>(e);
            drawable.clock.restart();
        });
        m_lua.set_function("getElapsedTimeAnimation", [&](RType::Runtime::ECS::Entity e) -> float {
            auto &drawable = m_registry.GetComponent<RType::Runtime::ECS::Components::Drawable>(e);
            return drawable.clock.getElapsedTime().asSeconds();
        });
        m_lua.set_function("restartClockScript", [&](RType::Runtime::ECS::Entity e) -> void {
            auto &script = m_registry.GetComponent<RType::Runtime::ECS::Components::Script>(e);
            script.clock.restart();
        });
        m_lua.set_function("getElapsedTimeScript", [&](RType::Runtime::ECS::Entity e) -> float {
            auto &script = m_registry.GetComponent<RType::Runtime::ECS::Components::Script>(e);
            return script.clock.getElapsedTime().asSeconds();
        });
        m_lua.set_function("destroyEntity", [&](RType::Runtime::ECS::Entity e) -> void {
            if (isServer()) {
                if (m_networkHandler.get() == nullptr)
                    return;
                ServerNetworkHandler *serverNetworkHandler =
                    static_cast<ServerNetworkHandler *>(m_networkHandler.get());
                SKIP_EXCEPTIONS({
                    auto &controllable = m_registry.GetComponent<RType::Runtime::ECS::Components::Controllable>(e);
                    controllable.isActive = false;
                    serverNetworkHandler->sendToAll(RType::Network::PacketEntityHide(e));
                    return;
                })
                SKIP_EXCEPTIONS({
                    auto &tag = m_registry.GetComponent<RType::Runtime::ECS::Components::Tag>(e);
                    serverNetworkHandler->sendToAll(RType::Network::PacketEntityDestroy(tag.uuid));
                    this->RemoveEntity(e);
                    return;
                })
            }
            this->RemoveEntity(e);
        });
        m_lua.set_function("addPrefab", [&](const char *path) -> RType::Runtime::ECS::Entity {
            if (isServer()) {
                ServerNetworkHandler *serverNetworkHandler =
                    static_cast<ServerNetworkHandler *>(m_networkHandler.get());
                RType::Runtime::ECS::Entity e = this->loadPrefab(path);
                SKIP_EXCEPTIONS({
                    auto &tag = m_registry.GetComponent<RType::Runtime::ECS::Components::Tag>(e);

                    tag.uuid = RType::Utils::UUIDS::generate();
                    serverNetworkHandler->sendToAll(RType::Network::PacketEntityCreate(tag.uuid, path));
                })
                SKIP_EXCEPTIONS({
                    auto &iaControllable = m_registry.GetComponent<RType::Runtime::ECS::Components::IAControllable>(e);
                    iaControllable.isActive = true;
                })
                return e;
            }
            return this->loadPrefab(path);
        });
        m_lua.set_function("playSound", [&](RType::Runtime::ECS::Entity e, const char *path) -> void {
            if (isServer())
                return;
#ifndef __APPLE__
            SKIP_EXCEPTIONS({
                auto &sound = AssetManager::getSoundBuffer(m_projectPath + "/assets/sounds/" + path + ".ogg");
                static sf::Sound s(sound);
                auto &transform = m_registry.GetComponent<RType::Runtime::ECS::Components::Transform>(e);
                s.setPosition(sf::Vector3f(transform.position.x, transform.position.y, 0));
                s.setPitch(RType::Utils::Random::GetFloat(0.8f, 1.2f));
                s.play();
            })
#endif
        });
        m_lua.set_function("getDrawable",
                           [&](RType::Runtime::ECS::Entity e) -> RType::Runtime::ECS::Components::Drawable {
                               auto &drawable = m_registry.GetComponent<RType::Runtime::ECS::Components::Drawable>(e);
                               return drawable;
                           });

        // Network functions
        m_lua.set_function("networkSendPosToServer", [&](RType::Runtime::ECS::Entity e) -> void {
            if (isServer() || m_networkHandler == nullptr)
                return;
            auto &transform = m_registry.GetComponent<RType::Runtime::ECS::Components::Transform>(e);
            ClientNetworkHandler *clientNetworkHandler = static_cast<ClientNetworkHandler *>(m_networkHandler.get());
            clientNetworkHandler->sendToServer(RType::Network::PacketControllableMove(
                e, transform.position.x, transform.position.y, transform.rotation.x, transform.rotation.y));
        });
        m_lua.set_function("networkSendInputToServer", [&](const std::string &input) -> void {
            if (isServer() || m_networkHandler == nullptr) {
                RTYPE_LOG_WARN("networkSendInputToServer lua function cannot be called on server");
                return;
            }
            ClientNetworkHandler *clientNetworkHandler = static_cast<ClientNetworkHandler *>(m_networkHandler.get());
            clientNetworkHandler->sendToServer(RType::Network::PacketClientInput(input));
        });
        m_lua.set_function("networkSendEntityUpdateToAll", [&](RType::Runtime::ECS::Entity e) -> void {
            if (!isServer() || m_networkHandler == nullptr) {
                RTYPE_LOG_WARN("networkSendEntityUpdateToAll lua function cannot be called on client");
                return;
            }
            SKIP_EXCEPTIONS({
                ServerNetworkHandler *serverNetworkHandler =
                    static_cast<ServerNetworkHandler *>(m_networkHandler.get());
                auto &tag = m_registry.GetComponent<RType::Runtime::ECS::Components::Tag>(e);

                if (tag.uuid.empty()) {
                    RTYPE_LOG_WARN("networkSendEntityUpdateToAll lua function cannot be called on entity without uuid "
                                   "(it's not a prefab ?)");
                    return;
                }
                json j;
                Serializer::saveEntity(*this, e, j);
                std::string jString = j.dump();
                serverNetworkHandler->sendToAll(RType::Network::PacketEntityUpdate(tag.uuid, jString));
            })
        });

        m_lua.set_exception_handler(
            [](lua_State *L, sol::optional<const std::exception &> maybe_exception, sol::string_view what) {
            if (maybe_exception) {
                const std::exception &ex = *maybe_exception;
                RTYPE_LOG_ERROR("An exception occurred in a function called from Lua: {0}: {1}", what, ex.what());
            } else {
                RTYPE_LOG_ERROR("An exception occurred in a function called from Lua: {0}", what);
            }
            return sol::stack::push(L, what);
        });
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
        m_startUpdateTime = std::chrono::high_resolution_clock::now();
        if (event.type == sf::Event::Resized)
            HandleResizeEvent(event);

        for (const auto &entity : m_entities) {
            f_updateSprites(entity);
            f_updateTransforms(entity);

            m_startScriptTime = std::chrono::high_resolution_clock::now();
            f_updateScripts(entity);
            m_endScriptTime = std::chrono::high_resolution_clock::now();
        }
        if (m_networkHandler != nullptr)
            m_networkHandler->update();
        m_endUpdateTime = std::chrono::high_resolution_clock::now();
    }

    void Runtime::Update()
    {
        m_startUpdateTime = std::chrono::high_resolution_clock::now();
        for (const auto &entity : m_entities) {
            f_updateScripts(entity);
        }
        if (m_networkHandler != nullptr)
            m_networkHandler->update();
        m_endUpdateTime = std::chrono::high_resolution_clock::now();
    }

    void Runtime::Render()
    {
        m_startRenderTime = std::chrono::high_resolution_clock::now();

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

        m_endRenderTime = std::chrono::high_resolution_clock::now();
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
        LuaApi::ExecFunctionOnEntity(*this, m_lua, "onDestroy", entity);
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
        RType::Runtime::ECS::Entity entity = Serializer::loadPrefab(*this, path);

        LuaApi::ExecFunctionOnEntity(*this, m_lua, "onStart", entity);
        return entity;
    }

    void Runtime::setProjectPath(const std::string &projectPath)
    {
        m_projectPath = projectPath;
        std::ifstream file(m_projectPath + "/project.json");
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open project.json");
        }
        nlohmann::json j;
        file >> j;
        loadScene(m_projectPath + "/" + j["startScene"].get<std::string>());
        file.close();

        for (auto &entity : GetEntities()) {
            LuaApi::ExecFunctionOnEntity(*this, m_lua, "onStart", entity);
        }
    }

    std::tuple<float, float, float> Runtime::getDebugTimes() const
    {
        auto scriptTime =
            std::chrono::duration_cast<std::chrono::microseconds>(m_endScriptTime - m_startScriptTime).count() /
            1000.0f;
        auto renderTime =
            std::chrono::duration_cast<std::chrono::microseconds>(m_endRenderTime - m_startRenderTime).count() /
            1000.0f;
        auto updateTime =
            std::chrono::duration_cast<std::chrono::microseconds>(m_endUpdateTime - m_startUpdateTime).count() /
            1000.0f;
        return {scriptTime, renderTime, updateTime};
    }

    void Runtime::f_updateTransforms(RType::Runtime::ECS::Entity entity)
    {
        SKIP_EXCEPTIONS({
            const auto &transform = m_registry.GetComponent<RType::Runtime::ECS::Components::Transform>(entity);
            auto &drawable = m_registry.GetComponent<RType::Runtime::ECS::Components::Drawable>(entity);
            drawable.sprite.setPosition(transform.position);
            drawable.sprite.setRotation(transform.rotation.x);
            drawable.sprite.setScale(transform.scale);
            drawable.sprite.setOrigin(drawable.sprite.getLocalBounds().width / 2,
                                      drawable.sprite.getLocalBounds().height / 2);
            if (drawable.isAnimated && drawable.autoPlay) {
                float timeElapsed = drawable.clock.getElapsedTime().asSeconds();
                if (timeElapsed < drawable.frameDuration) {
                    return;
                }
                if (drawable.currentFrame >= drawable.frameCount) {
                    drawable.currentFrame = 0;
                    drawable.rect.left = drawable.startPosition;
                } else {
                    ++drawable.currentFrame;
                    drawable.rect.left += drawable.leftDecal;
                }
                drawable.sprite.setTextureRect((sf::IntRect)drawable.rect);
                drawable.clock.restart();
            }
        })
        /*
        SKIP_EXCEPTIONS({
            const auto &transform = m_registry.GetComponent<RType::Runtime::ECS::Components::Transform>(entity);
            auto &circle = m_registry.GetComponent<RType::Runtime::ECS::Components::CircleShape>(entity);
            circle.circle.setOrigin(circle.circle.getLocalBounds().width / 2,
                                    circle.circle.getLocalBounds().height / 2);
            circle.circle.setPosition(transform.position);
            circle.circle.setRotation(transform.rotation.x);
            circle.circle.setScale(transform.scale);
        })*/
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
                if (drawable.isAnimated) {
                    drawable.sprite.setTextureRect((sf::IntRect)drawable.rect);
                }
            }
            // TODO: handle rect + animations but in other if statement
        })
    }

    void Runtime::f_updateColliders(RType::Runtime::ECS::Entity entity, const std::string &path)
    {
        RType::Runtime::ECS::Components::CollisionBox collisionBox;
        try {
            collisionBox = m_registry.GetComponent<RType::Runtime::ECS::Components::CollisionBox>(entity);
        } catch (std::exception &e) {
            return;
        }

        for (auto &e : m_entities) {
            if (e == entity)
                continue;

            RType::Runtime::ECS::Components::CollisionBox collisionBox2;
            try {
                collisionBox2 = m_registry.GetComponent<RType::Runtime::ECS::Components::CollisionBox>(e);
            } catch (std::exception &e) {
                continue;
            }

            SKIP_EXCEPTIONS({
                auto &t1 = m_registry.GetComponent<RType::Runtime::ECS::Components::Transform>(entity);
                auto &t2 = m_registry.GetComponent<RType::Runtime::ECS::Components::Transform>(e);

                if (t1.position.x - collisionBox.width / 2 < t2.position.x + collisionBox2.width / 2 &&
                    t1.position.x + collisionBox.width / 2 > t2.position.x - collisionBox2.width / 2 &&
                    t1.position.y - collisionBox.height / 2 < t2.position.y + collisionBox2.height / 2 &&
                    t1.position.y + collisionBox.height / 2 > t2.position.y - collisionBox2.height / 2) {
                    LuaApi::ExecFunctionOnCurrentLoadedScript(m_lua, path, "onCollision", entity, e);
                }
            })
        }
    }

    void Runtime::f_updateScripts(RType::Runtime::ECS::Entity entity)
    {
        SKIP_EXCEPTIONS({
            auto &controllable = m_registry.GetComponent<RType::Runtime::ECS::Components::Controllable>(entity);
            if (!controllable.isActive)
                return;
            if (!isServer() && controllable.isServerControl)
                return;
        })
        SKIP_EXCEPTIONS({
            auto &script = m_registry.GetComponent<RType::Runtime::ECS::Components::Script>(entity);

            for (int i = 0; i < 6; i++) {
                std::string currentPath = script.paths[i];
                if (currentPath.empty())
                    continue;

                std::string scriptName = currentPath.substr(currentPath.find_last_of("/") + 1);
                // sol::table &env = m_environmentScripts[scriptName];

                if (isServer()) {
                    LuaApi::ExecFunction(m_lua, LuaApi::GetScriptPath(m_projectPath, script.paths[i]), "updateServer",
                                         entity);
                    f_updateColliders(entity, script.paths[i]);
                } else {
                    LuaApi::ExecFunction(m_lua, LuaApi::GetScriptPath(m_projectPath, script.paths[i]), "update",
                                         entity);
                }
            }
        })

        SKIP_EXCEPTIONS({
            auto &controllable = m_registry.GetComponent<RType::Runtime::ECS::Components::IAControllable>(entity);

            if (!isServer())
                return;
            LuaApi::ExecFunction(m_lua, LuaApi::GetScriptPath(m_projectPath, controllable.scriptPath), "updateServer",
                                 entity);
            f_updateColliders(entity, controllable.scriptPath);
        })
    }

} // namespace RType::Runtime
