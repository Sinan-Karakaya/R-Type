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
        /**
         * @brief Initializes the registry.
         */
        void Init()
        {
            m_componentManager = std::make_unique<ComponentManager>();
            m_entityManager = std::make_unique<EntityManager>();
            m_systemManager = std::make_unique<SystemManager>();
        }

        /**
         * @brief Creates a new entity.
         * 
         * @return The newly created entity.
         */
        Entity CreateEntity() { return m_entityManager->CreateEntity(); }

        /**
         * @brief Destroys an entity.
         *
         * This function destroys the specified entity, removing all its components from the registry.
         *
         * @param entity The entity to destroy.
         */
        void DestroyEntity(Entity entity)
        {
            m_entityManager->DestroyEntity(entity);
            m_componentManager->EntityDestroyed(entity);
            m_systemManager->EntityDestroyed(entity);
        }

        template <typename T>
        /**
         * @brief Registers a component in the ECS registry.
         */
        void RegisterComponent()
        {
            m_componentManager->RegisterComponent<T>();
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
            m_componentManager->AddComponent<T>(entity, component);

            auto signature = m_entityManager->GetSignature(entity);
            signature.set(m_componentManager->GetComponentType<T>(), true);
            m_entityManager->SetSignature(entity, signature);

            m_systemManager->EntitySignatureChanged(entity, signature);
        }

        template <typename T>
        /**
         * @brief Removes a component from an entity.
         *
         * This function removes the specified component from the given entity.
         *
         * @param entity The entity from which to remove the component.
         */
        void RemoveComponent(Entity entity)
        {
            m_componentManager->RemoveComponent<T>(entity);

            auto signature = m_entityManager->GetSignature(entity);
            signature.set(m_componentManager->GetComponentType<T>(), false);
            m_entityManager->SetSignature(entity, signature);

            m_systemManager->EntitySignatureChanged(entity, signature);
        }

        template <typename T>
        /**
         * @brief Retrieves the component associated with the given entity.
         *
         * @tparam T The type of the component.
         * @param entity The entity for which to retrieve the component.
         * @return A reference to the component associated with the entity.
         */
        T &GetComponent(Entity entity)
        {
            return m_componentManager->GetComponent<T>(entity);
        }

        template <typename T>
        /**
         * @brief Retrieves the component type of the entity.
         *
         * @return The component type of the entity.
         */
        ComponentType GetComponentType()
        {
            return m_componentManager->GetComponentType<T>();
        }

        template <typename T>
        /**
         * @brief Registers a system of type T.
         *
         * @tparam T The type of the system to register.
         * @return std::shared_ptr<T> A shared pointer to the registered system.
         */
        std::shared_ptr<T> RegisterSystem()
        {
            return m_systemManager->RegisterSystem<T>();
        }

        template <typename T>
        /**
         * @brief Sets the signature for a system.
         *
         * This function sets the signature for a system in the ECS registry.
         * The signature determines which components the system will process.
         *
         * @param signature The signature to set for the system.
         */
        void SetSystemSignature(Signature signature)
        {
            m_systemManager->SetSignature<T>(signature);
        }

        /**
         * @brief Runs all the systems in the registry.
         */
        void RunSystems() { m_systemManager->RunSystems(); }

    private:
        std::unique_ptr<ComponentManager> m_componentManager;
        std::unique_ptr<EntityManager> m_entityManager;
        std::unique_ptr<SystemManager> m_systemManager;
    };

} // namespace RType::Runtime::ECS
