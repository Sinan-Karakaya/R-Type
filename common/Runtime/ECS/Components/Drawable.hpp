#pragma once

#include <map>
#include <tuple>
#include <unordered_map>
#include <vector>

#include <SFML/Graphics.hpp>

namespace RType::ECS::Components
{

    // TODO: Change this to a string, and use an AssetManager to give a reference to a Sprite or Texture
    struct Drawable {
        char *path = nullptr;

        sf::Sprite sprite;

        bool isAnimated = false;
        sf::FloatRect bounds;
        /**
         * @brief The key is the position of the bounds in the texture
         * The value is the size of the bounds in the sprite
         */
        std::map<sf::Vector2f, sf::Vector2f> animations;
        std::vector<float> animationSpeeds;
    };

    struct Controllable {
        /**
         * @brief The first bool is used to know if the key is pressed or not
         * The tuple holds 2 values: One for the keyboard, and one for the joystick
         * This way we can support both keyboard and joystick inputs
         */
        std::unordered_map<bool, std::tuple<sf::Keyboard::Key, sf::Joystick::Axis>> controls;

        bool isNetworked = false;
    };

} // namespace RType::ECS::Components
