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

        m_registry.registerComponent<RType::ECS::Components::Transformable>();
        m_registry.registerComponent<RType::ECS::Components::Velocity>();
        m_registry.registerComponent<RType::ECS::Components::Drawable>();
        m_registry.registerComponent<RType::ECS::Components::Controllable>();
    }

    void Runtime::Destroy()
    {
        m_renderTexture.clear();
    }

    void Runtime::Update(sf::Event &event)
    {
        if (event.type == sf::Event::Resized)
            HandleResizeEvent(event);

        // Call function to handle events, using the controllable component or something

        // Call scripts to execute their logic
        m_registry.runSystems();
    }

    void Runtime::Update()
    {
        m_registry.runSystems();
    }

    void Runtime::Render()
    {
        m_renderTexture.clear(sf::Color::Black);

        for (const auto &drawable : m_registry.getComponents<RType::ECS::Components::Drawable>()) {
            m_renderTexture.draw(drawable.sprite);
        }

        m_renderTexture.display();
    }

    sf::Sprite Runtime::GetRenderTextureSprite()
    {
        const sf::Texture &texture = m_renderTexture.getTexture();
        sf::Sprite sprite(texture);
        return sprite;
    }

    void Runtime::HandleResizeEvent(sf::Event event)
    {
        m_renderTexture.create(event.size.width, event.size.height);
        m_camera.setSize(event.size.width, event.size.height);
        m_renderTexture.setView(m_camera);
    }

} // namespace RType::Runtime
