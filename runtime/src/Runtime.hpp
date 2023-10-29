/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Runtime
*/

#pragma once

#include <SFML/Graphics.hpp>

#include "Runtime/IRuntime.hpp"

namespace RType::Runtime {

class Runtime : public IRuntime {
  public:
    Runtime() = default;
    ~Runtime() = default;

    // Init and destroy are used to for example, leave the game and return to the lobby selection, etc...
    // This prevents us from reloading the dynamic library each time we want to change the game state
    void Init(int width = 1920, int height = 1080);
    void Destroy();

    void Update();
    void Render();

    sf::Sprite GetRenderTextureSprite();
    const sf::RenderTexture &GetRenderTexture() const {
        return m_renderTexture;
    }

    void HandleResizeEvent(sf::Event event);
};

} // namespace RType::Runtime
