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
        EntityManager()
        {
            for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
                m_availableEntities.push(entity);
        }

        Entity CreateEntity()
        {
            Entity id = m_availableEntities.front();
            m_availableEntities.pop();
            ++m_livingEntityCount;

            return id;
        }

        void DestroyEntity(Entity entity)
        {
            m_signatures[entity].reset();
            m_availableEntities.push(entity);
            --m_livingEntityCount;
        }

        void SetSignature(Entity entity, Signature signature) { m_signatures[entity] = signature; }

        Signature GetSignature(Entity entity) { return m_signatures[entity]; }

    private:
        std::queue<Entity> m_availableEntities;
        std::array<Signature, MAX_ENTITIES> m_signatures;
        uint32_t m_livingEntityCount = 0;
    };

} // namespace RType::Runtime::ECS
