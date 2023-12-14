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
#include <nlohmann/json.hpp>

#define MAX_COMPONENTS 32

using ComponentType = std::uint8_t;
using Signature = std::bitset<MAX_COMPONENTS>;

namespace RType::Runtime::ECS::Components
{
    struct Transform {
        sf::Vector2f position;
        sf::Vector2f rotation;
        sf::Vector2f scale;

        friend void from_json(const nlohmann::json &j, Transform &t)
        {
            t.position.x = j["position"]["x"];
            t.position.y = j["position"]["y"];
            t.rotation.x = j["rotation"]["x"];
            t.rotation.y = j["rotation"]["y"];
            t.scale.x = j["scale"]["x"];
            t.scale.y = j["scale"]["y"];
        }

        friend void to_json(nlohmann::json &j, const Transform &t)
        {
            j["type"] = "Transform";
            j["position"]["x"] = t.position.x;
            j["position"]["y"] = t.position.y;
            j["rotation"]["x"] = t.rotation.x;
            j["rotation"]["y"] = t.rotation.y;
            j["scale"]["x"] = t.scale.x;
            j["scale"]["y"] = t.scale.y;
        }
    };

    struct Script {
        char path[256] = {0};

        friend void from_json(const nlohmann::json &j, Script &s)
        {
            strcpy(s.path, j["path"].get<std::string>().c_str());
        }

        friend void to_json(nlohmann::json &j, const Script &s)
        {
            j["type"] = "Script";
            j["path"] = s.path;
        }
    };

    struct Gravity {
        sf::Vector2f force;

        friend void from_json(const nlohmann::json &j, Gravity &g)
        {
            g.force.x = j["force"]["x"];
            g.force.y = j["force"]["y"];
        }

        friend void to_json(nlohmann::json &j, const Gravity &g)
        {
            j["type"] = "Gravity";
            j["force"]["x"] = g.force.x;
            j["force"]["y"] = g.force.y;
        }
    };

    struct RigidBody {
        sf::Vector2f velocity;
        sf::Vector2f acceleration;

        friend void from_json(const nlohmann::json &j, RigidBody &r)
        {
            r.velocity.x = j["velocity"]["x"];
            r.velocity.y = j["velocity"]["y"];
            r.acceleration.x = j["acceleration"]["x"];
            r.acceleration.y = j["acceleration"]["y"];
        }

        friend void to_json(nlohmann::json &j, const RigidBody &r)
        {
            j["type"] = "RigidBody";
            j["velocity"]["x"] = r.velocity.x;
            j["velocity"]["y"] = r.velocity.y;
            j["acceleration"]["x"] = r.acceleration.x;
            j["acceleration"]["y"] = r.acceleration.y;
        }
    };

    struct Drawable {
        sf::Sprite sprite;
        sf::Texture texture;
        sf::FloatRect rect = sf::FloatRect(0, 0, 100, 100);
        char path[256] = {0};
        bool isLoaded = false;

        bool isAnimated = false;
        int frameCount = 0;
        int currentFrame = 0;
        float frameDuration = 0.f;
        float leftDecal = 0.f;
        sf::FloatRect firstFrameRect = sf::FloatRect(0, 0, 100, 100);

        friend void from_json(const nlohmann::json &j, Drawable &d)
        {
            std::strcpy(d.path, j["path"].get<std::string>().c_str());
            d.isAnimated = j["isAnimated"];
            d.frameCount = j["frameCount"];
            d.currentFrame = j["currentFrame"];
            d.frameDuration = j["frameDuration"];
            d.leftDecal = j["leftDecal"];
            d.firstFrameRect.left = j["firstFrameRect"]["left"];
            d.firstFrameRect.top = j["firstFrameRect"]["top"];
            d.firstFrameRect.width = j["firstFrameRect"]["width"];
            d.firstFrameRect.height = j["firstFrameRect"]["height"];
            d.rect.left = j["rect"]["left"];
            d.rect.top = j["rect"]["top"];
            d.rect.width = j["rect"]["width"];
            d.rect.height = j["rect"]["height"];
        }

        friend void to_json(nlohmann::json &j, const Drawable &d)
        {
            j["type"] = "Drawable";
            j["path"] = d.path;
            j["isAnimated"] = d.isAnimated;
            j["frameCount"] = d.frameCount;
            j["currentFrame"] = d.currentFrame;
            j["frameDuration"] = d.frameDuration;
            j["leftDecal"] = d.leftDecal;
            j["firstFrameRect"]["left"] = d.firstFrameRect.left;
            j["firstFrameRect"]["top"] = d.firstFrameRect.top;
            j["firstFrameRect"]["width"] = d.firstFrameRect.width;
            j["firstFrameRect"]["height"] = d.firstFrameRect.height;
            j["rect"]["left"] = d.rect.left;
            j["rect"]["top"] = d.rect.top;
            j["rect"]["width"] = d.rect.width;
            j["rect"]["height"] = d.rect.height;
        }
    };

    struct CircleShape {
        sf::CircleShape circle = sf::CircleShape(10);

        friend void from_json(const nlohmann::json &j, CircleShape &c)
        {
            c.circle.setRadius(j["radius"]);
            c.circle.setFillColor(sf::Color(j["color"]["r"], j["color"]["g"], j["color"]["b"]));
        }

        friend void to_json(nlohmann::json &j, const CircleShape &c)
        {
            j["type"] = "CircleShape";
            j["radius"] = c.circle.getRadius();
            j["color"]["r"] = c.circle.getFillColor().r;
            j["color"]["g"] = c.circle.getFillColor().g;
            j["color"]["b"] = c.circle.getFillColor().b;
        }
    };

} // namespace RType::Runtime::ECS::Components
