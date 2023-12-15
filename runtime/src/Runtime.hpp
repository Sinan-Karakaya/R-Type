/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Runtime
*/

#pragma once

#define SOL_ALL_SAFETIES_ON 1

#include <SFML/Graphics.hpp>

#include "RType.hpp"

#include "Runtime/ECS/Components/Components.hpp"
#include "Runtime/ECS/Registry.hpp"
#include "Serializer/Serializer.hpp"

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
        void InitLua();
        void Destroy();

        void Update(sf::Event &event);
        void Update();
        void Render();

        sf::Sprite GetRenderTextureSprite();
        const sf::RenderTexture &GetRenderTexture() const { return m_renderTexture; }

        std::vector<RType::Runtime::ECS::Entity> &GetEntities() { return m_entities; }
        RType::Runtime::ECS::Registry &GetRegistry() { return m_registry; }

        RType::Runtime::ECS::Entity AddEntity();
        void RemoveEntity(RType::Runtime::ECS::Entity entity);

        void HandleResizeEvent(sf::Event event);
        void HandleResizeEvent(float x, float y);

        bool loadScene(const std::string &path);
        bool saveScene(const std::string &path);

        void setProjectPath(const std::string &projectPath) { m_projectPath = projectPath; }
        const std::string &getProjectPath() const { return m_projectPath; }
    };

} // namespace RType::Runtime
