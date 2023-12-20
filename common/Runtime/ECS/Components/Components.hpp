/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Components
*/

#pragma once

#include <bitset>
#include <cstdint>
#include <unordered_map>

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

    struct Tag {
        char tag[256] = {0};

        friend void from_json(const nlohmann::json &j, Tag &t)
        {
            std::strcpy(t.tag, j["tag"].get<std::string>().c_str());
        }

        friend void to_json(nlohmann::json &j, const Tag &t)
        {
            j["type"] = "Tag";
            j["tag"] = t.tag;
        }
    };

    struct Script {
        char paths[6][256] = {0};

        friend void from_json(const nlohmann::json &j, Script &s)
        {
            std::array<std::string, 6> scripts = j["paths"];

            for (int i = 0; i < 6; i++)
                std::strcpy(s.paths[i], scripts[i].c_str());
        }

        friend void to_json(nlohmann::json &j, const Script &s)
        {
            j["type"] = "Script";
            j["paths"] = nlohmann::json::array();
            for (int i = 0; i < 6; i++)
                j["paths"].push_back(s.paths[i]);
        }
    };

    struct RigidBody {
        float mass = 1.f;
        sf::Vector2f velocity;
        sf::Vector2f acceleration;
        bool useGravity = false;
        bool isKinematic = false;

        friend void from_json(const nlohmann::json &j, RigidBody &r)
        {
            r.velocity.x = j["velocity"]["x"];
            r.velocity.y = j["velocity"]["y"];
            r.acceleration.x = j["acceleration"]["x"];
            r.acceleration.y = j["acceleration"]["y"];
            r.useGravity = j["useGravity"];
            r.isKinematic = j["isKinematic"];
            r.mass = j["mass"];
        }

        friend void to_json(nlohmann::json &j, const RigidBody &r)
        {
            j["type"] = "RigidBody";
            j["velocity"]["x"] = r.velocity.x;
            j["velocity"]["y"] = r.velocity.y;
            j["acceleration"]["x"] = r.acceleration.x;
            j["acceleration"]["y"] = r.acceleration.y;
            j["useGravity"] = r.useGravity;
            j["isKinematic"] = r.isKinematic;
            j["mass"] = r.mass;
        }
    };

    struct Drawable {
        sf::Sprite sprite;
        sf::Texture texture;
        sf::FloatRect rect = sf::FloatRect(0, 0, 100, 100);
        char path[256] = {0};
        bool isLoaded = false;
        bool isCollidable = false;

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
            d.isCollidable = j["isCollidable"];
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
            j["isCollidable"] = d.isCollidable;
        }
    };

    struct CircleShape {
        sf::CircleShape circle = sf::CircleShape(10);
        bool isCollidable = false;

        friend void from_json(const nlohmann::json &j, CircleShape &c)
        {
            c.isCollidable = j["isCollidable"];
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
            j["isCollidable"] = c.isCollidable;
        }
    };

    struct Controllable {
        std::unordered_map<std::string, sf::Keyboard::Key> inputs;

        bool isServerControl = false;
        bool isActive = false;

        friend void from_json(const nlohmann::json &j, Controllable &c)
        {
            c.isServerControl = j["isServerControl"];
            c.isActive = j["isActive"];

            for (auto &input : j["inputs"]) {
                c.inputs[input["name"]] = static_cast<sf::Keyboard::Key>(input["key"].get<int>());
            }
        }

        friend void to_json(nlohmann::json &j, const Controllable &c)
        {
            j["type"] = "Controllable";
            j["isServerControl"] = c.isServerControl;
            j["isActive"] = c.isActive;

            j["inputs"] = nlohmann::json::array();
            for (auto &input : c.inputs) {
                j["inputs"].push_back(nlohmann::json::object());
                j["inputs"].back()["key"] = input.second;
                j["inputs"].back()["name"] = input.first;
            }
        }
    };

    struct UIRectangleElement {
        sf::RectangleShape rectangle;
        sf::Text text;
    };
} // namespace RType::Runtime::ECS::Components
