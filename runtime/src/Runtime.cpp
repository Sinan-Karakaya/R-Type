/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Runtime
*/

#include "Runtime.hpp"

extern "C" RType::Runtime::IRuntime *RuntimeEntry() {
    return new RType::Runtime::Runtime();
}

extern "C" void RuntimeDestroy(RType::Runtime::IRuntime *runtime) {
    delete runtime;
}

namespace RType::Runtime {

void Runtime::Init(int width, int height) {
    m_camera.setSize(width, height);
    m_renderTexture.create(width, height);
    m_renderTexture.setSmooth(true);
    m_renderTexture.setView(m_camera);
}

void Runtime::Destroy() {
    m_renderTexture.clear();
}

void Runtime::Update() {
    // Call class to handle events, based on what has been saved to a file i guess
    // to allow to set inputs in the editor if possible
}

void Runtime::Render() {
    m_renderTexture.clear(sf::Color::Black);

    // TODO: loop through drawables in scene, and draw them

    // TO DELETE
    sf::CircleShape shape;
    shape.setFillColor(sf::Color::Green);
    shape.setRadius(40.f);
    shape.setPosition(m_renderTexture.mapPixelToCoords(sf::Vector2i(100, 100)));
    m_renderTexture.draw(shape);
    // TO DELETE

    m_renderTexture.display();
}

sf::Sprite Runtime::GetRenderTextureSprite() {
    const sf::Texture &texture = m_renderTexture.getTexture();
    sf::Sprite sprite(texture);
    return sprite;
}

void Runtime::HandleResizeEvent(sf::Event event) {
    m_camera.setSize(event.size.width, event.size.height);
    m_renderTexture.setView(m_camera);
}

} // namespace RType::Runtime
