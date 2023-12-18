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
#include "Registry.hpp"

namespace RType::Runtime::ECS
{
    class Registry; // Forward declaration
}

namespace RType::Runtime::ECS
{

    class ISystem
    {
    public:
        std::set<Entity> entities;
        const char *scriptPath;
        std::unordered_set<std::string> luaFunc;

        // TODO: implement server script
        void run() { return; }
    };

    class SystemManager
    {
    public:
        template <typename T>
        std::shared_ptr<T> RegisterSystem(const char *scriptPath)
        {
            const char *typeName = typeid(T).name();

            if (m_systems.find(typeName) != m_systems.end()) {
                return std::static_pointer_cast<T>(m_systems[typeName]);
            }

            auto system = std::make_shared<T>(scriptPath);
            m_systems.insert({typeName, system});
            return system;
        }

        template <typename T>
        void SetSignature(Signature signature)
        {
            const char *typeName = typeid(T).name();

            if (m_systems.find(typeName) == m_systems.end()) {
                std::cerr << "System used before registered" << std::endl;
                return;
            }

            m_signatures.insert({typeName, signature});
        }

        void EntityDestroyed(Entity entity)
        {
            for (const auto &pair : m_systems) {
                const auto &system = pair.second;

                system->entities.erase(entity);
            }
        }

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

        void RunSystems()
        {
            for (const auto &pair : m_systems) {
                const auto &system = pair.second;
                system->run();
            }
        }

    private:
        std::unordered_map<const char *, Signature> m_signatures {};
        std::unordered_map<const char *, std::shared_ptr<ISystem>> m_systems {};
    };

} // namespace RType::Runtime::ECS
