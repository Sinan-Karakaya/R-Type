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
        m_registry.RegisterComponent<RType::Runtime::ECS::Components::Script>();

        InitLua();

        AssetManager::init();
    }

    void Runtime::InitLua()
    {
        // open some common libraries
        m_lua.open_libraries(sol::lib::base, sol::lib::package);

        ////////////////////////////////////////////////////////////////////////////
        //    Register all Components types as usertype :                         //
        //    - sf::Vector2f                                                      //
        //    - sf::FloatRect                                                     //
        //                                                                        //
        //    TODO: add all components (circleshape, sprite, texture, etc...)     //
        ////////////////////////////////////////////////////////////////////////////
        m_lua.new_usertype<sf::Vector2f>("vector", sol::constructors<sf::Vector2f(float, float)>(), "x",
                                         &sf::Vector2f::x, "y", &sf::Vector2f::y);
        m_lua.new_usertype<sf::FloatRect>("rect", sol::constructors<sf::FloatRect(float, float, float, float)>(),
                                          "left", &sf::FloatRect::left, "top", &sf::FloatRect::top, "width",
                                          &sf::FloatRect::width, "height", &sf::FloatRect::height);

        //////////////////////////////////////////////
        //  Register all Components as usertype :   //
        //       - Transform                        //
        //       - Script                           //
        //       - Gravity                          //
        //       - RigidBody                        //
        //       - Drawable                         //
        //       - CircleShape                      //
        //////////////////////////////////////////////
        m_lua.new_usertype<RType::Runtime::ECS::Components::Transform>(
            "transform",
            sol::constructors<RType::Runtime::ECS::Components::Transform(sf::Vector2f, sf::Vector2f, sf::Vector2f)>(),
            "position", &RType::Runtime::ECS::Components::Transform::position, "rotation",
            &RType::Runtime::ECS::Components::Transform::rotation, "scale",
            &RType::Runtime::ECS::Components::Transform::scale);
        /*
        m_lua.new_usertype<RType::Runtime::ECS::Components::Script>
        (
            "script", sol::constructors<RType::Runtime::ECS::Components::Script(const char *)>(),
            "path", &RType::Runtime::ECS::Components::Script::path
        );
        */
        m_lua.new_usertype<RType::Runtime::ECS::Components::Gravity>(
            "gravity", sol::constructors<RType::Runtime::ECS::Components::Gravity(sf::Vector2f)>(), "force",
            &RType::Runtime::ECS::Components::Gravity::force);
        m_lua.new_usertype<RType::Runtime::ECS::Components::RigidBody>(
            "rigidbody", sol::constructors<RType::Runtime::ECS::Components::RigidBody(sf::Vector2f, sf::Vector2f)>(),
            "velocity", &RType::Runtime::ECS::Components::RigidBody::velocity, "acceleration",
            &RType::Runtime::ECS::Components::RigidBody::acceleration);
        /*
        m_lua.new_usertype<RType::Runtime::ECS::Components::Drawable>
        (
            "drawable", sol::constructors<RType::Runtime::ECS::Components::Drawable(sf::Sprite, sf::Texture,
        sf::FloatRect, char *, bool, bool, int, int, float, float, sf::FloatRect)>(), "sprite",
        &RType::Runtime::ECS::Components::Drawable::sprite, "texture",
        &RType::Runtime::ECS::Components::Drawable::texture, "rect", &RType::Runtime::ECS::Components::Drawable::rect,
            "path", &RType::Runtime::ECS::Components::Drawable::path,
            "isLoaded", &RType::Runtime::ECS::Components::Drawable::isLoaded,
            "isAnimated", &RType::Runtime::ECS::Components::Drawable::isAnimated,
            "frameCount", &RType::Runtime::ECS::Components::Drawable::frameCount,
            "currentFrame", &RType::Runtime::ECS::Components::Drawable::currentFrame,
            "frameDuration", &RType::Runtime::ECS::Components::Drawable::frameDuration,
            "leftDecal", &RType::Runtime::ECS::Components::Drawable::leftDecal
            // "firstFrameRect", &RType::Runtime::ECS::Components::Drawable::firstFrameRect
        );
        */
        /*
        m_lua.new_usertype<RType::Runtime::ECS::Components::CircleShape>
        (
            "circleshape", sol::constructors<RType::Runtime::ECS::Components::CircleShape()>(),
            "circle", &RType::Runtime::ECS::Components::CircleShape::circle
        );
        */

        //////////////////////////////////////////////////////
        //  Register all getter functions :                 //
        //       - getComponentGravity                      //
        //       - getComponentRigidBody                    //
        //       - getComponentDrawable                     //
        //       - getComponentCircleShape                  //
        //////////////////////////////////////////////////////
        // runtime.GetRegistry().GetComponent<ECS::Components::Drawable>(e);
        m_lua.set_function("getComponentTransform", [&](RType::Runtime::ECS::Entity e) {
            return m_registry.GetComponent<RType::Runtime::ECS::Components::Transform>(e);
        });

        m_lua.set_function("getComponentGravity", [&](RType::Runtime::ECS::Entity e) {
            return m_registry.GetComponent<RType::Runtime::ECS::Components::Gravity>(e);
        });

        m_lua.set_function("getComponentRigidBody", [&](RType::Runtime::ECS::Entity e) {
            return m_registry.GetComponent<RType::Runtime::ECS::Components::RigidBody>(e);
        });

        m_lua.set_function("getComponentDrawable", [&](RType::Runtime::ECS::Entity e) {
            return m_registry.GetComponent<RType::Runtime::ECS::Components::Drawable>(e);
        });

        m_lua.set_function("getComponentCircleShape", [&](RType::Runtime::ECS::Entity e) {
            return m_registry.GetComponent<RType::Runtime::ECS::Components::CircleShape>(e);
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

        // Call function to handle events, using the controllable component or something
        int size = m_entities.size();
        int i = 0;
        for (const auto &entity : m_entities) {
            try {
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
            } catch (const std::exception &e) {
            }

            try {
                const auto &transform = m_registry.GetComponent<RType::Runtime::ECS::Components::Transform>(entity);
                auto &drawable = m_registry.GetComponent<RType::Runtime::ECS::Components::Drawable>(entity);
                drawable.sprite.setPosition(transform.position);
                drawable.sprite.setRotation(transform.rotation.x);
                drawable.sprite.setScale(transform.scale);
            } catch (const std::exception &e) {
            }
            try {
                const auto &transform = m_registry.GetComponent<RType::Runtime::ECS::Components::Transform>(entity);
                auto &circle = m_registry.GetComponent<RType::Runtime::ECS::Components::CircleShape>(entity);
                circle.circle.setPosition(transform.position);
                circle.circle.setRotation(transform.rotation.x);
                circle.circle.setScale(transform.scale);
            } catch (const std::exception &e) {
            }
        }

        // Call scripts to execute their logic
        m_registry.RunSystems(m_lua);
    }

    void Runtime::Update()
    {
        m_registry.RunSystems(m_lua);
    }

    void Runtime::Render()
    {
        m_renderTexture.clear(sf::Color::Black);

        for (const auto &entity : m_entities) {
            try {
                const auto &drawable = m_registry.GetComponent<RType::Runtime::ECS::Components::Drawable>(entity);
                m_renderTexture.draw(drawable.sprite);
            } catch (const std::exception &e) {
            }

            try {
                const auto &shape = m_registry.GetComponent<RType::Runtime::ECS::Components::CircleShape>(entity);
                m_renderTexture.draw(shape.circle);
            } catch (const std::exception &e) {
            }
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
