/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** IRuntime
*/

#pragma once

#include <SFML/Graphics.hpp>

namespace RType::Runtime {

class IRuntime {
  public:
    virtual ~IRuntime() = default;

    // Init and destroy are used to for example, leave the game and return to the lobby selection, etc...
    // This prevents us from reloading the dynamic library each time we want to change the game state
    virtual void Init(int width = 1920, int height = 1080) = 0;
    virtual void Destroy() = 0;

    virtual void Update() = 0;
    virtual void Render() = 0;

    virtual sf::Sprite GetRenderTextureSprite() = 0;
    virtual const sf::RenderTexture &GetRenderTexture() const = 0;

    /**
     * @brief This should only be used in the client for now
     */
    virtual void HandleResizeEvent(sf::Event event) = 0;

  protected:
    sf::RenderTexture m_renderTexture;
    sf::Event m_event;
    sf::View m_camera;
};

} // namespace RType::Runtime
