/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** Registry
*/

#pragma once

#include <any>
#include <functional>
#include <stdexcept>
#include <typeindex>
#include <unordered_map>

#include "Entity.hpp"
#include "SparseArray.hpp"

namespace RType::Runtime::ECS
{

    class Registry
    {
    public:
        template <class Component>
        SparseArray<Component> &registerComponent()
        {
            auto it = m_componentsArrays.find(std::type_index(typeid(Component)));
            if (it == m_componentsArrays.end()) {
                auto [it2, success] =
                    m_componentsArrays.emplace(std::type_index(typeid(Component)), SparseArray<Component> {});

                // can add &registry in lambda if needed
                m_componentsDestructors.emplace(std::type_index(typeid(Component)),
                                                [this](Registry &registry, const Entity &entity) {
                                                    //                registry.getComponents<Component>().erase(entity);

                                                    /**
                                                     * DO NOT REMOVE THIS LINE, AND DO NOT REMOVE REGISTRY PARAMETER
                                                     * WITHOUT IT THE PROGRAM WON'T COMPILE, AND WILL PRINT ERRORS THAT
                                                     * NO ONE CAN UNDERSTAND TRUST ME, I SPENT 2 HOURS TRYING TO
                                                     * UNDERSTAND WHY IT DIDN'T COMPILE
                                                     */
                                                    (void)registry;

                                                    this->killEntity(entity);
                                                });
                return std::any_cast<SparseArray<Component> &>(it2->second);
            }
            return std::any_cast<SparseArray<Component> &>(it->second);
        }

        template <class Component>
        SparseArray<Component> &getComponents()
        {
            auto it = m_componentsArrays.find(std::type_index(typeid(Component)));
            if (it == m_componentsArrays.end())
                throw std::runtime_error("Component not found");
            return std::any_cast<SparseArray<Component> &>(it->second);
        }

        template <class Component>
        const SparseArray<Component> &getComponents() const
        {
            auto it = m_componentsArrays.find(std::type_index(typeid(Component)));
            if (it == m_componentsArrays.end())
                throw std::runtime_error("Component not found");
            return std::any_cast<const SparseArray<Component> &>(it->second);
        }

        Entity spawnEntity() { return Entity {m_lastEntityId++}; }

        Entity entityFromIndex(std::size_t index) { return Entity {index}; }

        void killEntity(const Entity &entity)
        {
            for (auto &it : m_componentsDestructors)
                it.second(*this, entity);
        }

        template <typename Component>
        typename SparseArray<Component>::referenceType addComponent(const Entity &to, Component &&c)
        {
            return getComponents<Component>().insert_at(to, std::forward<Component>(c));
        }

        template <typename Component, typename... Params>
        typename SparseArray<Component>::referenceType emplaceComponent(const Entity &to, Params &&...p)
        {
            return getComponents<Component>().emplace_at(to, std::forward<Params>(p)...);
        }

        template <typename Component>
        void RemoveComponent(const Entity &to)
        {
            getComponents<Component>().erase(to);
        }

        template <class... Components, typename Function>
        void addSystem(Function &&f)
        {
            m_systems.emplace(std::type_index(typeid(std::tuple<Components...>)), std::forward<Function>(f));
        }

        // Run all registered system functions.
        void runSystems()
        {
            for (auto &it : m_systems)
                it.second(*this);
        }

    private:
        std::unordered_map<std::type_index, std::any> m_componentsArrays;
        std::unordered_map<std::type_index, std::function<void(Registry &, const Entity &)>> m_componentsDestructors;

        std::unordered_map<std::type_index, std::function<void(Registry &)>> m_systems;

        std::size_t m_lastEntityId = 0;
    };

} // namespace RType::Runtime::ECS
