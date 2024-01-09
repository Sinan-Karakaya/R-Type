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
#include "ECS/System.hpp"
#include "ECS/Registry.hpp"

#include "NetworkHandler.hpp"

namespace RType::Runtime
{

    class IRuntime
    {
    public:
        virtual ~IRuntime() = default;

        // Init and destroy are used to for example, leave the game and return to the lobby selection, etc...
        // This prevents us from reloading the dynamic library each time we want to change the game state
        /**
         * @brief Initializes the runtime.
         *
         * @param width The width of the screen.
         * @param height The height of the screen.
         * @param projectPath The path to the project.
         * @param isServer Flag indicating if the runtime is running as a server.
         */
        virtual void Init(int width = 1920, int height = 1080, const std::string &projectPath = "",
                          bool isServer = false) = 0;
        /**
         * @brief Destroys the object.
         *
         * This function is responsible for destroying the object and freeing any allocated resources.
         * It is a pure virtual function that must be implemented by derived classes.
         */
        virtual void Destroy() = 0;

        /**
         * @brief Updates the runtime with the given event.
         *
         * This function is called to update the runtime with the specified event.
         *
         * @param event The event to be processed.
         */
        virtual void Update(sf::Event &event) = 0;
        /**
         * @brief Updates the runtime.
         *
         * This function is responsible for updating the runtime.
         * It should be implemented by derived classes.
         */
        virtual void Update() = 0;
        /**
         * @brief Renders the runtime.
         *
         * This pure virtual function is responsible for rendering the runtime.
         * Subclasses must implement this function to provide the rendering functionality.
         */
        virtual void Render() = 0;

        /**
         * @brief Retrieves the sprite associated with the render texture.
         *
         * @return sf::Sprite The sprite associated with the render texture.
         */
        virtual sf::Sprite GetRenderTextureSprite() = 0;
        /**
         * @brief Returns the render texture used by the runtime.
         *
         * @return const sf::RenderTexture& The render texture.
         */
        virtual sf::RenderTexture &GetRenderTexture() const = 0;
        /**
         * @brief Handles the resize event.
         *
         * This function is called when a resize event occurs in the application.
         * It takes an sf::Event object as a parameter.
         *
         * @param event The sf::Event object representing the resize event.
         */
        virtual void HandleResizeEvent(sf::Event event) = 0;
        /**
         * @brief Handles the resize event.
         *
         * This function is called when the window is resized.
         *
         * @param x The new width of the window.
         * @param y The new height of the window.
         */
        virtual void HandleResizeEvent(float x, float y) = 0;

        /**
         * @brief: To add components to an entity, use the registry
         * We can't do it through the runtime because we would need to make the function templated AND virtual
         * Which is not possible in C++...
         */
        virtual RType::Runtime::ECS::Registry &GetRegistry() = 0;
        /**
         * @brief Retrieves the entities stored in the runtime.
         *
         * @return A reference to a vector of RType::Runtime::ECS::Entity objects.
         */
        virtual std::vector<RType::Runtime::ECS::Entity> &GetEntities() = 0;

        /**
         * @brief Adds a new entity to the runtime.
         *
         * @return The ID of the newly added entity.
         */
        virtual RType::Runtime::ECS::Entity AddEntity() = 0;
        /**
         * @brief Removes an entity from the runtime.
         *
         * @param entity The entity to be removed.
         */
        virtual void RemoveEntity(RType::Runtime::ECS::Entity entity) = 0;

        /**
         * @brief Loads a scene from the specified path.
         *
         * @param path The path to the scene file.
         * @return true if the scene was successfully loaded, false otherwise.
         */
        virtual bool loadScene(const std::string &path) = 0;
        /**
         * @brief Saves the current scene to a file.
         *
         * @param path The path to the file where the scene will be saved.
         * @return true if the scene was successfully saved, false otherwise.
         */
        virtual bool saveScene(const std::string &path) = 0;
        /**
         * @brief Saves the prefab of the given entity.
         *
         * @param entity The entity to save the prefab for.
         * @return true if the prefab was successfully saved, false otherwise.
         */
        virtual bool savePrefab(RType::Runtime::ECS::Entity entity) = 0;
        /**
         * @brief Loads a prefab from the specified path.
         *
         * @param path The path to the prefab file.
         * @return The entity representing the loaded prefab.
         */
        virtual RType::Runtime::ECS::Entity loadPrefab(const std::string &path) = 0;

        /**
         * @brief Sets the project path.
         *
         * This function sets the path of the project.
         *
         * @param projectPath The path of the project.
         */
        virtual void setProjectPath(const std::string &projectPath) = 0;
        /**
         * @brief Get the project path.
         *
         * @return const std::string& The project path.
         */
        virtual const std::string &getProjectPath() const = 0;

        /**
         * @brief Sets the paused state of the runtime.
         *
         * @param paused True to pause the runtime, false to resume it.
         */
        virtual void setPaused(bool paused) = 0;
        /**
         * @brief Checks if the runtime is currently paused.
         *
         * @return true if the runtime is paused, false otherwise.
         */
        virtual bool isPaused() const = 0;

        /**
         * @brief: returns the time it took to execute the scripts,
         * the time it took to render the scene and the total update time
         */
        virtual std::tuple<float, float, float> getDebugTimes() const = 0;

        /**
         * @brief Sets the server flag.
         *
         * This function is used to set the server flag, indicating whether the runtime is running as a server or not.
         *
         * @param isServer A boolean value indicating whether the runtime is running as a server.
         */
        virtual void setServer(bool isServer) = 0;
        /**
         * @brief Checks if the runtime is running as a server.
         *
         * @return true if the runtime is running as a server, false otherwise.
         */
        virtual bool isServer() const = 0;

        /**
         * @brief Sets the network handler for the runtime.
         *
         * This function sets the network handler that will be used by the runtime
         * to handle network communication.
         *
         * @param networkHandler The network handler to set.
         */
        virtual void setNetworkHandler(std::shared_ptr<RType::Network::NetworkHandler> networkHandler) = 0;
        /**
         * @brief Retrieves the network handler.
         *
         * @return A reference to the network handler.
         */
        virtual RType::Network::NetworkHandler &getNetworkHandler() = 0;

        virtual sol::state &getLua() = 0;

    protected:
        sf::RenderTexture m_renderTexture;
        sf::Event m_event;
        sf::View m_camera;

        RType::Runtime::ECS::Registry m_registry;
        std::vector<RType::Runtime::ECS::Entity> m_entities;

        sol::state m_lua;
        std::string m_projectPath;

        bool m_isPaused = false;

        std::chrono::high_resolution_clock::time_point m_startScriptTime;
        std::chrono::high_resolution_clock::time_point m_endScriptTime;
        std::chrono::high_resolution_clock::time_point m_startRenderTime;
        std::chrono::high_resolution_clock::time_point m_endRenderTime;
        std::chrono::high_resolution_clock::time_point m_startUpdateTime;
        std::chrono::high_resolution_clock::time_point m_endUpdateTime;

        bool m_isServer = false;
    };

} // namespace RType::Runtime
