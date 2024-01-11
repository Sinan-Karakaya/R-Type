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

#include "Network/Handler/ClientNetworkHandler.hpp"
#include "Network/Handler/ServerNetworkHandler.hpp"
#include "Runtime/NetworkHandler.hpp"

#include "Runtime/LuaApi.hpp"
#include "Utils/CrashUtils.hpp"
#include "Utils/Random.hpp"

#include "Systems/AnimationSystem.hpp"
#include "Systems/MoveableSystem.hpp"
#include "Systems/PhysicSystem.hpp"

#include "Systems/AnimationSystem.hpp"
#include "Systems/MoveableSystem.hpp"
#include "Systems/PhysicSystem.hpp"

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
        /**
         * @brief Init the runtime
         *
         * @param width The width of the window
         * @param height The height of the window
         * @param isServer To precise to the runtime if it's a server or not
         * @return void
         */
        void Init(int width = 1920, int height = 1080, const std::string &projectPath = "", bool isServer = false);

        /**
         * @brief Init the lua state
         *
         * @return void
         */
        void InitLua();

        void Destroy();

        void Update(sf::Event &event);
        void Update();

        void Render();

        sf::Sprite GetRenderTextureSprite();
        sf::RenderTexture &GetRenderTexture() const { return const_cast<sf::RenderTexture &>(m_renderTexture); }

        std::vector<RType::Runtime::ECS::Entity> &GetEntities() { return m_entities; }
        RType::Runtime::ECS::Registry &GetRegistry() { return m_registry; }

        RType::Runtime::ECS::Entity AddEntity();
        void RemoveEntity(RType::Runtime::ECS::Entity entity);

        void HandleResizeEvent(sf::Event event);
        void HandleResizeEvent(float x, float y);

        bool loadScene(const std::string &path);

        bool saveScene(const std::string &path);
        bool savePrefab(RType::Runtime::ECS::Entity entity);
        RType::Runtime::ECS::Entity loadPrefab(const std::string &path);

        void setProjectPath(const std::string &projectPath);
        const std::string &getProjectPath() const { return m_projectPath; }

        void setPaused(bool paused) { m_isPaused = paused; }
        bool isPaused() const { return m_isPaused; }

        std::tuple<float, float, float> getDebugTimes() const;

        /**
         * @brief set server
         *
         * @param isServer The server state
         * @return void
         */
        void setServer(bool isServer) { m_isServer = isServer; }

        /**
         * @brief get server
         *
         * @return bool
         */
        bool isServer() const { return m_isServer; }

        /**
         * @brief set the network handler
         *
         * @param networkHandler The network handler
         * @return void
         */
        void setNetworkHandler(std::shared_ptr<RType::Network::NetworkHandler> networkHandler)
        {
            m_networkHandler = networkHandler;
        }

        /**
         * @brief get the network handler
         *
         * @return RType::Network::NetworkHandler&
         */
        Network::NetworkHandler &getNetworkHandler() { return *m_networkHandler; }

        sol::state &getLua() { return m_lua; }

    private:
        void f_updateSprites(RType::Runtime::ECS::Entity entity);
        void f_updateColliders(RType::Runtime::ECS::Entity entity, const std::string &path);
        void f_updateScripts(RType::Runtime::ECS::Entity entity);

        std::shared_ptr<RType::Network::NetworkHandler> m_networkHandler = nullptr;
        std::chrono::high_resolution_clock::time_point m_lastUpdateTime;
        std::vector<std::string> m_events;
    };

} // namespace RType::Runtime
