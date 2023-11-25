#pragma once

#include <SFML/Graphics.hpp>

namespace RType::ECS::Components
{

// TODO: Change this to a string, and use an AssetManager to give a reference to a Sprite or Texture
struct Drawable {
    sf::Sprite sprite;
    sf::Texture texture;
};

struct Controllable {
    sf::Keyboard::Key up;
    sf::Keyboard::Key down;
    sf::Keyboard::Key left;
    sf::Keyboard::Key right;
};

// typedef struct Controllable {
//     bool isControllable;
// } Controllable;

} // namespace RType::ECS::Components
