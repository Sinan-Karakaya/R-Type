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
        m_registry.RegisterComponent<RType::Runtime::ECS::Components::Text>();

        m_registry.RegisterSystem<RType::Runtime::MoveableSystem>();
        Signature moveableSignature;
        moveableSignature.set(m_registry.GetComponentType<RType::Runtime::ECS::Components::Transform>());
        m_registry.SetSystemSignature<RType::Runtime::MoveableSystem>(moveableSignature);

        m_registry.RegisterSystem<RType::Runtime::AnimationSystem>();
        Signature animationSignature;
        animationSignature.set(m_registry.GetComponentType<RType::Runtime::ECS::Components::Drawable>());
        m_registry.SetSystemSignature<RType::Runtime::AnimationSystem>(animationSignature);

        m_registry.RegisterSystem<RType::Runtime::PhysicSystem>();
        Signature physicSignature;
        physicSignature.set(m_registry.GetComponentType<RType::Runtime::ECS::Components::Transform>());
        physicSignature.set(m_registry.GetComponentType<RType::Runtime::ECS::Components::RigidBody>());
        m_registry.SetSystemSignature<RType::Runtime::PhysicSystem>(physicSignature);

        InitLua();
        AssetManager::init();
    }

    void Runtime::InitLua()
    {
        m_lua.open_libraries(sol::lib::base, sol::lib::math);

        // Create tables env for each script file to able lua to store variables
        std::string folderPath;

        if (m_projectPath.empty()) {
            folderPath = "./assets/scripts/";
        } else {
            folderPath = m_projectPath + "/assets/scripts/";
        }
        for (const auto &entry : std::filesystem::directory_iterator(folderPath)) {
            if (entry.path().extension() != ".lua")
                continue;

            std::string scriptName = entry.path().filename().string();
            scriptName = scriptName.substr(0, scriptName.find_last_of(".")) + "Table";

            m_lua[scriptName] = m_lua.create_table();
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
        m_lua.new_usertype<RType::Runtime::ECS::Components::Text>(
            "text", "content", &RType::Runtime::ECS::Components::Text::content, "size",
            &RType::Runtime::ECS::Components::Text::fontSize);
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
        m_lua.set_function("getComponentText",
                           [&](RType::Runtime::ECS::Entity e) -> RType::Runtime::ECS::Components::Text & {
                               return m_registry.GetComponent<RType::Runtime::ECS::Components::Text>(e);
                           });
        m_lua.set_function("getComponentDrawable",
                           [&](RType::Runtime::ECS::Entity e) -> RType::Runtime::ECS::Components::Drawable & {
                               return m_registry.GetComponent<RType::Runtime::ECS::Components::Drawable>(e);
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
        m_lua.set_function("getElapsedTimeIAControllable", [&](RType::Runtime::ECS::Entity e) -> float {
            auto &iaControllable = m_registry.GetComponent<RType::Runtime::ECS::Components::IAControllable>(e);
            return iaControllable.clock.getElapsedTime().asSeconds();
        });
        m_lua.set_function("restartClockIAControllable", [&](RType::Runtime::ECS::Entity e) -> void {
            auto &iaControllable = m_registry.GetComponent<RType::Runtime::ECS::Components::IAControllable>(e);
            iaControllable.clock.restart();
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
            SKIP_EXCEPTIONS({
                auto &controllable = m_registry.GetComponent<RType::Runtime::ECS::Components::Controllable>(e);
                controllable.isActive = false;
                LuaApi::ExecFunctionOnEntity(*this, m_lua, "onDestroy", e);
                return;
            })
            SKIP_EXCEPTIONS({
                auto &iaControllable = m_registry.GetComponent<RType::Runtime::ECS::Components::IAControllable>(e);
                iaControllable.isActive = false;
                LuaApi::ExecFunctionOnEntity(*this, m_lua, "onDestroy", e);
                return;
            })
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

        m_lua.set_function("triggerEvent", [&](const std::string &eventName) -> void { m_events.push(eventName); });
        m_lua.set_function("loadScene", [&](const std::string &path) -> void { this->loadScene(path); });
        m_lua.set_function("getEntityByTag", [&](const std::string &wantedTag) -> RType::Runtime::ECS::Entity {
            for (auto &entity : GetEntities()) {
                auto &tag = m_registry.GetComponent<RType::Runtime::ECS::Components::Tag>(entity);
                if (std::string(tag.tag) == wantedTag) {
                    return entity;
                }
            }
            return 0;
        });
        m_lua.set_function("setText", [&](RType::Runtime::ECS::Entity e, const std::string &text) -> void {
            try {
                auto &textComponent = m_registry.GetComponent<RType::Runtime::ECS::Components::Text>(e);
                std::strcpy(textComponent.content, text.c_str());
            } catch (std::exception &ex) {
                RTYPE_LOG_ERROR("Try to setText on non text entity");
            }
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

        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> dt = currentTime - m_lastUpdateTime;
        m_lastUpdateTime = currentTime;

        m_registry.RunSystems(dt.count());

        std::queue<std::string> events = m_events;
        while (!m_events.empty())
            m_events.pop();

        for (const auto &entity : m_entities) {
            f_updateSprites(entity);

            m_startScriptTime = std::chrono::high_resolution_clock::now();
            f_updateScripts(entity, events);
            m_endScriptTime = std::chrono::high_resolution_clock::now();
        }
        if (m_networkHandler != nullptr)
            m_networkHandler->update();
        m_endUpdateTime = std::chrono::high_resolution_clock::now();
    }

    void Runtime::Update()
    {
        m_startUpdateTime = std::chrono::high_resolution_clock::now();

        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> dt = currentTime - m_lastUpdateTime;
        m_lastUpdateTime = currentTime;

        m_registry.RunSystems(dt.count());

        std::queue<std::string> events = m_events;
        while (!m_events.empty())
            m_events.pop();

        for (const auto &entity : m_entities) {
            f_updateScripts(entity, events);
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

            SKIP_EXCEPTIONS({
                const auto &text = m_registry.GetComponent<RType::Runtime::ECS::Components::Text>(entity);

                m_renderTexture.draw(text.text);
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

    bool Runtime::loadScene(const std::string &path, bool keepLua)
    {
        return RType::Runtime::Serializer::loadScene(path, *this, keepLua);
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
        bool isMultiplayer = j["isMultiplayer"].get<bool>();

        m_isMultiplayer = isMultiplayer;
        if (isMultiplayer) {
            for (auto &entity : GetEntities()) {
                SKIP_EXCEPTIONS({
                    auto &controllable = GetRegistry().GetComponent<ECS::Components::Controllable>(entity);
                    controllable.isActive = false;
                })
            }
        }

        for (auto &entity : GetEntities()) {
            LuaApi::ExecFunctionOnEntity(*this, m_lua, "onStart", entity);
        }

        if (j.contains("disabledSystems")) {
            for (auto &system : j["disabledSystems"]) {
                for (auto &s : m_registry.GetSystems()) {
                    if (s.second->GetName() == system.get<std::string>()) {
                        s.second->enabled = false;
                    }
                }
            }
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

    void Runtime::f_updateSprites(RType::Runtime::ECS::Entity entity)
    {
        SKIP_EXCEPTIONS({
            auto &drawable = m_registry.GetComponent<RType::Runtime::ECS::Components::Drawable>(entity);
            const std::string drawableFullPath = m_projectPath + "/assets/sprites/" + drawable.path;
            drawable.texture = AssetManager::getTexture(drawableFullPath);
            drawable.sprite.setTexture(drawable.texture);
            drawable.sprite.setOrigin(drawable.sprite.getLocalBounds().width / 2,
                                      drawable.sprite.getLocalBounds().height / 2);
            drawable.isLoaded = true;
            if (drawable.isAnimated) {
                drawable.sprite.setTextureRect((sf::IntRect)drawable.rect);
            }
        })
        SKIP_EXCEPTIONS({
            auto &text = m_registry.GetComponent<RType::Runtime::ECS::Components::Text>(entity);
            const std::string textFullPath = m_projectPath + "/assets/fonts/" + text.fontPath;

            if (std::string(text.fontPath).empty() || std::string(text.content).empty())
                return;
            try {
                text.text.setFont(AssetManager::getFont(textFullPath));
            } catch (std::exception &e) {
                RTYPE_LOG_ERROR("Failed to load font {0}", textFullPath);
            }
            text.text.setString(text.content);
            text.text.setCharacterSize(text.fontSize);
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

    void Runtime::f_updateScripts(RType::Runtime::ECS::Entity entity, const std::queue<std::string> &events)
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

                std::queue<std::string> eventsCopy = events;
                while (!eventsCopy.empty()) {
                    LuaApi::ExecFunction(m_lua, LuaApi::GetScriptPath(m_projectPath, currentPath), "onEvent", entity,
                                         eventsCopy.front());
                    eventsCopy.pop();
                }

                if (isServer()) {
                    LuaApi::ExecFunction(m_lua, LuaApi::GetScriptPath(m_projectPath, script.paths[i]), "updateServer",
                                         entity);
                    f_updateColliders(entity, script.paths[i]);
                } else {
                    LuaApi::ExecFunction(m_lua, LuaApi::GetScriptPath(m_projectPath, script.paths[i]), "update",
                                         entity);
                    if (!m_isMultiplayer) {
                        f_updateColliders(entity, script.paths[i]);
                    }
                }
            }
        })

        SKIP_EXCEPTIONS({
            auto &controllable = m_registry.GetComponent<RType::Runtime::ECS::Components::IAControllable>(entity);

            if (!isServer() && m_isMultiplayer)
                return;

            if (controllable.isActive == false)
                return;

            std::queue<std::string> eventsCopy = events;
            while (!eventsCopy.empty()) {
                LuaApi::ExecFunction(m_lua, LuaApi::GetScriptPath(m_projectPath, controllable.scriptPath), "onEvent",
                                     entity, eventsCopy.front());
                eventsCopy.pop();
            }

            if (m_isMultiplayer) {
                LuaApi::ExecFunction(m_lua, LuaApi::GetScriptPath(m_projectPath, controllable.scriptPath),
                                     "updateServer", entity);
            } else {
                LuaApi::ExecFunction(m_lua, LuaApi::GetScriptPath(m_projectPath, controllable.scriptPath), "update",
                                     entity);
            }
            f_updateColliders(entity, controllable.scriptPath);
        })
    }

} // namespace RType::Runtime
