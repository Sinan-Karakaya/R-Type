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

#include "Runtime/NetworkHandler.hpp"
#include "Network/Handler/ServerNetworkHandler.hpp"

namespace RType::Runtime
{

    using Registry = RType::Runtime::ECS::Registry;

    class Runtime : public IRuntime
    {
    public:
        /**
         * @brief Runtime constructor
         */
        Runtime() = default;
        /**
         * @brief Runtime destructor
         */
        ~Runtime() = default;

        // Init and destroy are used to for example, leave the game and return to the lobby selection, etc...
        // This prevents us from reloading the dynamic library each time we want to change the game state
        /**
         * @brief Init the runtime
         *
         * @param width The width of the window
         * @param height The height of the window
         * @param isServer To precise to the runtime if it's a server or not
         * @return void
         */
        void Init(int width = 1920, int height = 1080, bool isServer = false);

        /**
         * @brief Init the lua state
         *
         * @return void
         */
        void InitLua();

        /**
         * @brief Destroy the runtime
         *
         * @return void
         */
        void Destroy();

        /**
         * @brief Update the runtime
         *
         * @param event The event to handle
         * @return void
         */
        void Update(sf::Event &event);

        /**
         * @brief Render the runtime
         *
         * @return void
         */
        void Update();

        /**
         * @brief Render the runtime
         *
         * @return void
         */
        void Render();

        /**
         * @brief Get the RenderTexture Sprite
         *
         * @return sf::Sprite
         */
        sf::Sprite GetRenderTextureSprite();

        /**
         * @brief Get the RenderTexture
         *
         * @return sf::RenderTexture
         */
        const sf::RenderTexture &GetRenderTexture() const { return m_renderTexture; }

        /**
         * @brief Get Entities
         *
         * @return std::vector<RType::Runtime::ECS::Entity>
         */
        std::vector<RType::Runtime::ECS::Entity> &GetEntities() { return m_entities; }

        /**
         * @brief Get Registry
         *
         * @return RType::Runtime::ECS::Registry
         */
        RType::Runtime::ECS::Registry &GetRegistry() { return m_registry; }

        /**
         * @brief Add an entity
         *
         * @return RType::Runtime::ECS::Entity
         */
        RType::Runtime::ECS::Entity AddEntity();

        /**
         * @brief Remove an entity
         *
         * @param entity The entity to remove
         * @return void
         */
        void RemoveEntity(RType::Runtime::ECS::Entity entity);

        /**
         * @brief Handle the resize event
         *
         * @param event The event to handle
         * @return void
         */
        void HandleResizeEvent(sf::Event event);

        /**
         * @brief Handle the resize event
         *
         * @param x The x position
         * @param y The y position
         * @return void
         */
        void HandleResizeEvent(float x, float y);

        /**
         * @brief Load a scene
         *
         * @param path The path to the scene
         * @return bool
         */
        bool loadScene(const std::string &path);

        /**
         * @brief Save a scene
         *
         * @param path The path to the scene
         * @return bool
         */
        bool saveScene(const std::string &path);
        bool savePrefab(RType::Runtime::ECS::Entity entity);
        RType::Runtime::ECS::Entity loadPrefab(const std::string &path);

        /**
         * @brief set the project path
         *
         * @param projectPath The path to the project
         * @return void
         */
        void setProjectPath(const std::string &projectPath) { m_projectPath = projectPath; }

        /**
         * @brief get the project path
         *
         * @return const std::string&
         */
        const std::string &getProjectPath() const { return m_projectPath; }

        /**
         * @brief set paused
         *
         * @param paused The paused state
         * @return void
         */
        void setPaused(bool paused) { m_isPaused = paused; }

        /**
         * @brief get paused
         *
         * @return bool
         */
        bool isPaused() const { return m_isPaused; }

        Network::NetworkHandler &getNetworkHandler() { return *m_networkHandler; }

    private:
        /**
         * @brief update the transforms
         *
         * @param entity The entity to update
         * @return void
         */
        void f_updateTransforms(RType::Runtime::ECS::Entity entity);

        /**
         * @brief update the sprites
         *
         * @param entity The entity to update
         * @return void
         */
        void f_updateSprites(RType::Runtime::ECS::Entity entity);

        /**
         * @brief update the colliders
         *
         * @param entity The entity to update
         * @param path The path to the collider
         * @return void
         */
        void f_updateColliders(RType::Runtime::ECS::Entity entity, const std::string &path);

        /**
         * @brief update the scripts
         *
         * @param entity The entity to update
         * @return void
         */
        void f_updateScripts(RType::Runtime::ECS::Entity entity);

        std::unique_ptr<RType::Network::NetworkHandler> m_networkHandler;
    };

} // namespace RType::Runtime
