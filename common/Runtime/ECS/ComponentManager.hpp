/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ComponentManager
*/

#pragma once

#include <memory>
#include <typeinfo>

#include "../../RType.hpp"
#include "ComponentArray.hpp"

namespace RType::Runtime::ECS
{

    class ComponentManager
    {
    public:
        template <typename T>
        /**
         * @brief Registers a component.
         *
         * This function is used to register a component in the component manager.
         *
         * @tparam T The type of the component to register.
         */
        void RegisterComponent()
        {
            std::string typeName = std::string(typeid(T).name());
            typeName = typeName.substr(typeName.find(" ") + 1);

            if (m_componentTypes.find(typeName) != m_componentTypes.end()) {
                std::cerr << "Registering component type more than once." << std::endl;
                return;
            }

            m_componentTypes.insert({typeName, m_nextComponentType});
            m_componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});

            ++m_nextComponentType;
        }

        template <typename T>
        /**
         * @brief Gets the component type.
         * 
         * @return The component type.
         */
        ComponentType GetComponentType()
        {
            std::string typeName = std::string(typeid(T).name());
            typeName = typeName.substr(typeName.find(" ") + 1);

            if (m_componentTypes.find(typeName) == m_componentTypes.end()) {
                std::cerr << "Component not registered before use." << std::endl;
                return ComponentType {};
            }

            return m_componentTypes[typeName];
        }

        template <typename T>
        /**
         * @brief Adds a component to an entity.
         * 
         * @param entity The entity to add the component to.
         * @param component The component to add.
         */
        void AddComponent(Entity entity, T component)
        {
            GetComponentArray<T>()->InsertData(entity, component);
        }

        template <typename T>
        /**
         * @brief Removes a component from an entity.
         * 
         * @param entity The entity from which to remove the component.
         */
        void RemoveComponent(Entity entity)
        {
            GetComponentArray<T>()->RemoveData(entity);
        }

        template <typename T>
        /**
         * @brief Retrieves the component associated with the given entity.
         * 
         * @tparam T The type of the component.
         * @param entity The entity for which to retrieve the component.
         * @return T& A reference to the component associated with the entity.
         */
        T &GetComponent(Entity entity)
        {
            return GetComponentArray<T>()->GetData(entity);
        }

        /**
         * @brief Called when an entity is destroyed.
         * 
         * @param entity The entity that was destroyed.
         */
        void EntityDestroyed(Entity entity)
        {
            for (const auto &pair : m_componentArrays) {
                const auto &component = pair.second;
                component->EntityDestroyed(entity);
            }
        }

    private:
        std::unordered_map<std::string, ComponentType> m_componentTypes {};
        std::unordered_map<std::string, std::shared_ptr<IComponentArray>> m_componentArrays {};
        ComponentType m_nextComponentType {};

        template <typename T>
        /**
         * @brief Retrieves the component array for a specific component type.
         * 
         * @tparam T The component type.
         * @return std::shared_ptr<ComponentArray<T>> The component array.
         */
        std::shared_ptr<ComponentArray<T>> GetComponentArray()
        {
            std::string typeName = std::string(typeid(T).name());
            typeName = typeName.substr(typeName.find(" ") + 1);

            if (m_componentArrays.find(typeName) == m_componentArrays.end()) {
                std::cerr << "Component not registered before use." << std::endl;
                return nullptr;
            }

            return std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[typeName]);
        }
    };

} // namespace RType::Runtime::ECS
