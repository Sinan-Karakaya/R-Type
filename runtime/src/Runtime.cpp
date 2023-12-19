/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Runtime
*/

#include "Runtime.hpp"

struct transform {
    int x;
    int y;
    sf::Vector2f v;
};

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

    void Runtime::Init(int width, int height)
    {
        m_camera.setSize(width, height);
        m_renderTexture.create(width, height);
        m_renderTexture.setSmooth(true);
        m_renderTexture.setView(m_camera);

        m_registry.Init();
        m_registry.RegisterComponent<RType::Runtime::ECS::Components::Transform>();
        m_registry.RegisterComponent<RType::Runtime::ECS::Components::Gravity>();
        m_registry.RegisterComponent<RType::Runtime::ECS::Components::RigidBody>();
        m_registry.RegisterComponent<RType::Runtime::ECS::Components::Drawable>();
        m_registry.RegisterComponent<RType::Runtime::ECS::Components::CircleShape>();
        m_registry.RegisterComponent<RType::Runtime::ECS::Components::UIRectangleElement>();
        m_registry.RegisterComponent<RType::Runtime::ECS::Components::Script>();
        m_registry.RegisterComponent<RType::Runtime::ECS::Components::Controllable>();
        m_registry.RegisterComponent<RType::Runtime::ECS::Components::IAControllable>();

        InitLua();

        //AssetManager::init();
    }

    void Runtime::InitLua()
    {
        m_lua.open_libraries(sol::lib::base);

        m_lua.new_usertype<sf::Vector2f>("vector", sol::constructors<sf::Vector2f(float, float)>(), "x",
                                         &sf::Vector2f::x, "y", &sf::Vector2f::y);

        m_lua.new_usertype<RType::Runtime::ECS::Components::Transform>(
            "transform",
            sol::constructors<RType::Runtime::ECS::Components::Transform(sf::Vector2f, sf::Vector2f, sf::Vector2f)>(),
            "position", &RType::Runtime::ECS::Components::Transform::position, "rotation",
            &RType::Runtime::ECS::Components::Transform::rotation, "scale",
            &RType::Runtime::ECS::Components::Transform::scale);
        m_lua.new_usertype<RType::Runtime::ECS::Components::RigidBody>(
            "rigidbody", sol::constructors<RType::Runtime::ECS::Components::RigidBody(sf::Vector2f, sf::Vector2f)>(),
            "velocity", &RType::Runtime::ECS::Components::RigidBody::velocity, "acceleration",
            &RType::Runtime::ECS::Components::RigidBody::acceleration);
        m_lua.new_usertype<RType::Runtime::ECS::Components::Gravity>(
            "gravity", sol::constructors<RType::Runtime::ECS::Components::Gravity(sf::Vector2f)>(), "force",
            &RType::Runtime::ECS::Components::Gravity::force);
        m_lua.new_usertype<RType::Runtime::ECS::Components::Controllable>(
            "controllable", sol::constructors<RType::Runtime::ECS::Components::Controllable(bool)>(), "isActive",
            &RType::Runtime::ECS::Components::Controllable::isActive);
        m_lua.new_usertype<RType::Runtime::ECS::Components::IAControllable>(
            "iacontrollable", sol::constructors<RType::Runtime::ECS::Components::IAControllable(bool)>(), "isActive",
            &RType::Runtime::ECS::Components::IAControllable::isActive);

        // TODO: implement all getters
        m_lua.set_function("getComponentTransform",
                           [&](RType::Runtime::ECS::Entity e) -> RType::Runtime::ECS::Components::Transform & {
                               return m_registry.GetComponent<RType::Runtime::ECS::Components::Transform>(e);
                           });
        m_lua.set_function("getComponentRigidBody",
                           [&](RType::Runtime::ECS::Entity e) -> RType::Runtime::ECS::Components::RigidBody & {
                               return m_registry.GetComponent<RType::Runtime::ECS::Components::RigidBody>(e);
                           });
        m_lua.set_function("getComponentGravity",
                           [&](RType::Runtime::ECS::Entity e) -> RType::Runtime::ECS::Components::Gravity & {
                               return m_registry.GetComponent<RType::Runtime::ECS::Components::Gravity>(e);
                           });
        m_lua.set_function("getComponentControllable",
                           [&](RType::Runtime::ECS::Entity e) -> RType::Runtime::ECS::Components::Controllable & {
                               return m_registry.GetComponent<RType::Runtime::ECS::Components::Controllable>(e);
                           });
        m_lua.set_function("getComponentIAControllable",
                           [&](RType::Runtime::ECS::Entity e) -> RType::Runtime::ECS::Components::IAControllable & {
                               return m_registry.GetComponent<RType::Runtime::ECS::Components::IAControllable>(e);
                           });
    }

    void Runtime::Destroy()
    {
        for (const auto &entity : m_entities)
            this->RemoveEntity(entity);
        m_renderTexture.clear();
    }

    void Runtime::Update(sf::Event &event)
    {
        if (event.type == sf::Event::Resized)
            HandleResizeEvent(event);

        for (const auto &entity : m_entities) {
            SKIP_EXCEPTIONS({
                auto &drawable = m_registry.GetComponent<RType::Runtime::ECS::Components::Drawable>(entity);
                const std::string drawableFullPath = m_projectPath + "/assets/sprites/" + drawable.path;
                if (!drawable.isLoaded && std::filesystem::exists(drawableFullPath) &&
                    drawableFullPath.ends_with(".png")) {
                    drawable.texture = AssetManager::getTexture(drawableFullPath);
                    drawable.sprite.setTexture(drawable.texture);
                    drawable.sprite.setOrigin(drawable.sprite.getLocalBounds().width / 2,
                                              drawable.sprite.getLocalBounds().height / 2);
                    drawable.isLoaded = true;
                }
                // TODO: handle rect + animations but in other if statement
            })

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
                circle.circle.setPosition(transform.position);
                circle.circle.setRotation(transform.rotation.x);
                circle.circle.setScale(transform.scale);
            })
            SKIP_EXCEPTIONS({
                auto &script = m_registry.GetComponent<RType::Runtime::ECS::Components::Script>(entity);

                std::string script_content = AssetManager::getScript(m_projectPath + "/assets/scripts/" + script.path);

                m_lua.script(script_content);
                sol::function f = m_lua["update"];
                std::cout << "entity: " << entity << std::endl;
                sol::protected_function_result res = f(entity);
                if (!res.valid()) {
                    sol::error err = res;
                    sol::call_status status = res.status();
                    std::cerr << "Error during script execution: " << err.what() << std::endl;
                }
            })
        }
        // TODO: implement server script
        // m_registry.RunSystems(m_lua, m_entities, m_registry, m_projectPath);
    }

    void Runtime::Update()
    {
        m_registry.RunSystems(m_lua, m_entities, m_registry, m_projectPath);
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
        m_camera.setSize(event.size.width, event.size.height);
        m_renderTexture.setView(m_camera);
    }

    void Runtime::HandleResizeEvent(float x, float y)
    {
        m_renderTexture.create(x, y);
        m_camera.setSize(x, y);
        m_renderTexture.setView(m_camera);
    }

    bool Runtime::loadScene(const std::string &path)
    {
        return RType::Runtime::Serializer::loadScene(path, *this);
    }

    bool Runtime::saveScene(const std::string &path)
    {
        return RType::Runtime::Serializer::saveScene(path, *this);
    }

} // namespace RType::Runtime
