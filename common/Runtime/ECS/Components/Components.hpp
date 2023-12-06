/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Components
*/

#pragma once

#include <bitset>
#include <cstdint>

#include <SFML/Graphics.hpp>

#define MAX_COMPONENTS 32

using ComponentType = std::uint8_t;
using Signature = std::bitset<MAX_COMPONENTS>;

namespace RType::Runtime::ECS::Components
{

    struct Transform {
        sf::Vector2f position;
        sf::Vector2f rotation;
        sf::Vector2f scale;
    };

    struct Gravity {
        sf::Vector2f force;
    };

    struct RigidBody {
        sf::Vector2f velocity;
        sf::Vector2f acceleration;
    };

    struct Drawable {
        sf::Sprite sprite;
        sf::Texture texture;
        sf::FloatRect rect = sf::FloatRect(0, 0, 100, 100);
        char path[256] = {0};

        bool isAnimated = false;
        int frameCount = 0;
        int currentFrame = 0;
        float frameDuration = 0.f;
        float leftDecal = 0.f;
        sf::FloatRect firstFrameRect = sf::FloatRect(0, 0, 100, 100);
    };

    struct CircleShape {
        sf::CircleShape circle = sf::CircleShape(10);
    };

} // namespace RType::Runtime::ECS::Components
