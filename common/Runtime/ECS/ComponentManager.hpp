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
        void AddComponent(Entity entity, T component)
        {
            GetComponentArray<T>()->InsertData(entity, component);
        }

        template <typename T>
        void RemoveComponent(Entity entity)
        {
            GetComponentArray<T>()->RemoveData(entity);
        }

        template <typename T>
        T &GetComponent(Entity entity)
        {
            return GetComponentArray<T>()->GetData(entity);
        }

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
