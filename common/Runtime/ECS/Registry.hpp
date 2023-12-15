/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Registry
*/

#pragma once

#include <memory>

#include "System.hpp"

namespace RType::Runtime::ECS
{

    class Registry
    {
    public:
        void Init()
        {
            m_componentManager = std::make_unique<ComponentManager>();
            m_entityManager = std::make_unique<EntityManager>();
            m_systemManager = std::make_unique<SystemManager>();
        }

        Entity CreateEntity() { return m_entityManager->CreateEntity(); }

        void DestroyEntity(Entity entity)
        {
            m_entityManager->DestroyEntity(entity);
            m_componentManager->EntityDestroyed(entity);
            m_systemManager->EntityDestroyed(entity);
        }

        template <typename T>
        void RegisterComponent()
        {
            m_componentManager->RegisterComponent<T>();
        }

        template <typename T>
        void AddComponent(Entity entity, T component)
        {
            m_componentManager->AddComponent<T>(entity, component);

            auto signature = m_entityManager->GetSignature(entity);
            signature.set(m_componentManager->GetComponentType<T>(), true);
            m_entityManager->SetSignature(entity, signature);

            m_systemManager->EntitySignatureChanged(entity, signature);
        }

        template <typename T>
        void RemoveComponent(Entity entity)
        {
            m_componentManager->RemoveComponent<T>(entity);

            auto signature = m_entityManager->GetSignature(entity);
            signature.set(m_componentManager->GetComponentType<T>(), false);
            m_entityManager->SetSignature(entity, signature);

            m_systemManager->EntitySignatureChanged(entity, signature);
        }

        template <typename T>
        T &GetComponent(Entity entity)
        {
            return m_componentManager->GetComponent<T>(entity);
        }

        template <typename T>
        ComponentType GetComponentType()
        {
            return m_componentManager->GetComponentType<T>();
        }

        template <typename T>
        std::shared_ptr<T> RegisterSystem()
        {
            return m_systemManager->RegisterSystem<T>();
        }

        template <typename T>
        void SetSystemSignature(Signature signature)
        {
            m_systemManager->SetSignature<T>(signature);
        }

        void RunSystems(sol::state &lua, std::vector<RType::Runtime::ECS::Entity> entities,
                            RType::Runtime::ECS::Registry& registry, std::string projectPath) { 
            m_systemManager->RunSystems(lua, entities, registry, projectPath);
        }

    private:
        std::unique_ptr<ComponentManager> m_componentManager;
        std::unique_ptr<EntityManager> m_entityManager;
        std::unique_ptr<SystemManager> m_systemManager;
    };

} // namespace RType::Runtime::ECS
