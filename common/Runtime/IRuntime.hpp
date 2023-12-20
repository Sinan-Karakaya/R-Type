/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** IRuntime
*/

#pragma once

#define SOL_ALL_SAFETIES_ON 1

#include <unordered_map>

#include <SFML/Graphics.hpp>
#include <sol/sol.hpp>

#include "ECS/Components/Components.hpp"
#include "ECS/Entity.hpp"
#include "ECS/Registry.hpp"

namespace RType::Runtime
{

    class IRuntime
    {
    public:
        virtual ~IRuntime() = default;

        // Init and destroy are used to for example, leave the game and return to the lobby selection, etc...
        // This prevents us from reloading the dynamic library each time we want to change the game state
        virtual void Init(int width = 1920, int height = 1080) = 0;
        virtual void Destroy() = 0;

        virtual void Update(sf::Event &event) = 0;
        virtual void Update() = 0;
        virtual void Render() = 0;

        virtual sf::Sprite GetRenderTextureSprite() = 0;
        virtual const sf::RenderTexture &GetRenderTexture() const = 0;
        virtual void HandleResizeEvent(sf::Event event) = 0;
        virtual void HandleResizeEvent(float x, float y) = 0;

        /**
         * @brief: To add components to an entity, use the registry
         * We can't do it through the runtime because we would need to make the function templated AND virtual
         * Which is not possible in C++...
         */
        virtual RType::Runtime::ECS::Registry &GetRegistry() = 0;
        virtual std::vector<RType::Runtime::ECS::Entity> &GetEntities() = 0;

        virtual RType::Runtime::ECS::Entity AddEntity() = 0;
        virtual void RemoveEntity(RType::Runtime::ECS::Entity entity) = 0;

        virtual bool loadScene(const std::string &path) = 0;
        virtual bool saveScene(const std::string &path) = 0;
        virtual bool savePrefab(RType::Runtime::ECS::Entity entity) = 0;
        virtual RType::Runtime::ECS::Entity loadPrefab(const std::string &path) = 0;

        virtual void setProjectPath(const std::string &projectPath) = 0;
        virtual const std::string &getProjectPath() const = 0;

        virtual void setPaused(bool paused) = 0;
        virtual bool isPaused() const = 0;

    protected:
        sf::RenderTexture m_renderTexture;
        sf::Event m_event;
        sf::View m_camera;

        RType::Runtime::ECS::Registry m_registry;
        std::vector<RType::Runtime::ECS::Entity> m_entities;

        sol::state m_lua;
        std::string m_projectPath;

        bool m_isPaused = false;
    };

} // namespace RType::Runtime
