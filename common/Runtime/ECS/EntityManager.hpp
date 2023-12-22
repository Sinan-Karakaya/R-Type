/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** EntityManager
*/

#pragma once

#include <cstdint>
#include <queue>
#include <stdexcept>
#include <vector>

#include "Components/Components.hpp"
#include "Entity.hpp"

namespace RType::Runtime::ECS
{

    class EntityManager
    {
    public:
        /**
         * @brief The EntityManager class is responsible for managing entities in the ECS system.
         * 
         * It provides functionality for creating, destroying, and querying entities.
         */
        EntityManager()
        {
            for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
                m_availableEntities.push(entity);
        }

        /**
         * @brief Creates a new entity.
         * 
         * @return The newly created entity.
         */
        Entity CreateEntity()
        {
            Entity id = m_availableEntities.front();
            m_availableEntities.pop();
            ++m_livingEntityCount;

            return id;
        }

        /**
         * @brief Destroys an entity.
         *
         * This function destroys the specified entity, removing it from the entity manager and freeing its associated resources.
         *
         * @param entity The entity to be destroyed.
         */
        void DestroyEntity(Entity entity)
        {
            m_signatures[entity].reset();
            m_availableEntities.push(entity);
            --m_livingEntityCount;
        }

        /**
         * @brief Sets the signature for a given entity.
         * 
         * @param entity The entity for which to set the signature.
         * @param signature The signature to set for the entity.
         */
        void SetSignature(Entity entity, Signature signature) { m_signatures[entity] = signature; }

        /**
         * @brief Retrieves the signature of the specified entity.
         *
         * @param entity The entity for which to retrieve the signature.
         * @return The signature of the entity.
         */
        Signature GetSignature(Entity entity) { return m_signatures[entity]; }

    private:
        std::queue<Entity> m_availableEntities;
        std::array<Signature, MAX_ENTITIES> m_signatures;
        uint32_t m_livingEntityCount = 0;
    };

} // namespace RType::Runtime::ECS
