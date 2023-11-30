/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Runtime
*/

#pragma once

#include <SFML/Graphics.hpp>

#include "RType.hpp"

#include "Runtime/ECS/Components/Drawable.hpp"
#include "Runtime/ECS/Components/Transforms.hpp"
#include "Runtime/ECS/Registry.hpp"

namespace RType::Runtime
{

    using Registry = RType::Runtime::ECS::Registry;

    class Runtime : public IRuntime
    {
    public:
        Runtime() = default;
        ~Runtime() = default;

        // Init and destroy are used to for example, leave the game and return to the lobby selection, etc...
        // This prevents us from reloading the dynamic library each time we want to change the game state
        void Init(int width = 1920, int height = 1080);
        void Destroy();

        void Update(const sf::Event &event);
        void Render();

        sf::Sprite GetRenderTextureSprite();
        const sf::RenderTexture &GetRenderTexture() const { return m_renderTexture; }

        std::unordered_map<std::size_t, RType::Runtime::ECS::Entity> &GetEntities() { return m_entities; }
        RType::Runtime::ECS::Registry &GetRegistry() { return m_registry; }

        void HandleResizeEvent(sf::Event event);
    };

} // namespace RType::Runtime
