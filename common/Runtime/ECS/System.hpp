/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** System
*/

#pragma once

#include <filesystem>
#include <set>
#include <unordered_set>

#include "ComponentManager.hpp"
#include "EntityManager.hpp"

namespace RType::Runtime::ECS
{
    class Registry;

    class ISystem
    {
    public:
        std::set<Entity> entities;

        virtual void run(Registry &registry) = 0;
    };

    class SystemManager
    {
    public:
        template <typename T>
        /**
         * @brief Registers a system
         *
         * @return A shared pointer to the registered system.
         */
        std::shared_ptr<T> RegisterSystem()
        {
            const char *typeName = typeid(T).name();

            if (m_systems.find(typeName) != m_systems.end()) {
                return std::static_pointer_cast<T>(m_systems[typeName]);
            }

            auto system = std::make_shared<T>();
            m_systems.insert({typeName, system});
            return system;
        }

        template <typename T>
        /**
         * @brief Sets the signature of the system.
         *
         * This function sets the signature of the system, which defines the component types
         * that the system operates on.
         *
         * @param signature The signature to set for the system.
         */
        void SetSignature(Signature signature)
        {
            const char *typeName = typeid(T).name();

            if (m_systems.find(typeName) == m_systems.end()) {
                std::cerr << "System used before registered" << std::endl;
                return;
            }

            m_signatures.insert({typeName, signature});
        }

        /**
         * @brief Called when an entity is destroyed.
         *
         * @param entity The entity that was destroyed.
         */
        void EntityDestroyed(Entity entity)
        {
            for (const auto &pair : m_systems) {
                const auto &system = pair.second;

                system->entities.erase(entity);
            }
        }

        /**
         * @brief Called when the signature of an entity has changed.
         *
         * @param entity The entity whose signature has changed.
         * @param entitySignature The new signature of the entity.
         */
        void EntitySignatureChanged(Entity entity, Signature entitySignature)
        {
            for (const auto &pair : m_systems) {
                const auto &type = pair.first;
                const auto &system = pair.second;
                const auto &m_systemSignature = m_signatures[type];

                if ((entitySignature & m_systemSignature) == m_systemSignature)
                    system->entities.insert(entity);
                else
                    system->entities.erase(entity);
            }
        }

        /**
         * @brief Runs the systems in the ECS.
         *
         * This function is responsible for executing all the systems in the ECS.
         * It iterates over each system and calls their respective update functions.
         *
         * @note This function should be called once per frame in the game loop.
         */
        void RunSystems(Registry &registry)
        {
            for (const auto &pair : m_systems) {
                const auto &system = pair.second;
                system->run(registry);
            }
        }

    private:
        std::unordered_map<const char *, Signature> m_signatures {};
        std::unordered_map<const char *, std::shared_ptr<ISystem>> m_systems {};
    };

} // namespace RType::Runtime::ECS
