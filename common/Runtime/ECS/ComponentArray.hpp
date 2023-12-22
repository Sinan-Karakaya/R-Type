/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ComponentArray
*/

#pragma once

#include <array>
#include <unordered_map>

#include "../../RType.hpp"
#include "EntityManager.hpp"

namespace RType::Runtime::ECS
{

    class IComponentArray
    {
    public:
        virtual ~IComponentArray() = default;
        virtual void EntityDestroyed(Entity entity) = 0;
    };

    template <typename T>
    class ComponentArray : public IComponentArray
    {
    public:
        void InsertData(Entity entity, T component)
        {
            if (m_entityToIndexMap.find(entity) != m_entityToIndexMap.end()) {
                std::cerr << "Component added to same entity more than once." << std::endl;
                return;
            }

            std::uint32_t newIndex = m_size;
            m_entityToIndexMap[entity] = newIndex;
            m_indexToEntityMap[newIndex] = entity;
            m_componentArray[newIndex] = component;
            ++m_size;
        }

        void RemoveData(Entity entity)
        {
            if (m_entityToIndexMap.find(entity) == m_entityToIndexMap.end()) {
                // std::cerr << "Removing non-existent component." << std::endl;
                return;
            }

            std::uint32_t indexOfRemovedEntity = m_entityToIndexMap[entity];
            std::uint32_t indexOfLastElement = m_size - 1;
            m_componentArray[indexOfRemovedEntity] = m_componentArray[indexOfLastElement];

            Entity entityOfLastElement = m_indexToEntityMap[indexOfLastElement];
            m_entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
            m_indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

            m_entityToIndexMap.erase(entity);
            m_indexToEntityMap.erase(indexOfLastElement);

            --m_size;
        }

        T &GetData(Entity entity)
        {
            if (m_entityToIndexMap.find(entity) == m_entityToIndexMap.end()) {
                throw std::runtime_error("Retrieving non-existent component.");
            }

            return m_componentArray[m_entityToIndexMap[entity]];
        }

        void EntityDestroyed(Entity entity)
        {
            if (m_entityToIndexMap.find(entity) != m_entityToIndexMap.end())
                RemoveData(entity);
        }

    private:
        std::array<T, MAX_COMPONENTS> m_componentArray;
        std::unordered_map<Entity, std::uint32_t> m_entityToIndexMap;
        std::unordered_map<std::uint32_t, Entity> m_indexToEntityMap;
        std::uint32_t m_size;
    };

} // namespace RType::Runtime::ECS
