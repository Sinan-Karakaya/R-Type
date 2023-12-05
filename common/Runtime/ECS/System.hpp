/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** System
*/

#pragma once

#include <set>

#include "ComponentManager.hpp"

namespace RType::Runtime::ECS
{

    class ISystem
    {
    public:
        std::set<Entity> entities;
        const char *scriptPath;

        // TODO: call lua script
        void run(sol::state &lua, std::vector<const char *> luaFunc= {"update", "start", "destroy", "updateServer", "startServer", "destroyServer"})
        {
            try {
                // load the lua script from the file
                lua.load_file(scriptPath);
                for (const auto &functionName : luaFunc) {
                    sol::optional<sol::protected_function> run_update = lua[functionName];
                    // Check if the function exists
                    if (run_update) {
                        // This tells sol2 to not throw an exception on error but instead return a protected_function_result that we can check for validity
                        sol::protected_function_result result = run_update.value()();
                        // Check if the result is valid, and if not, print the error message
                        if (!result.valid()) {
                            sol::error err = result;
                            std::cerr << "Error loading or executing Lua script '" << scriptPath << "': " << err.what() << std::endl;
                            // We can choose to throw an exception or handle the error in another way
                        }
                    } else {
                        std::cerr << "Error loading Lua script '" << scriptPath << "': function 'update' not found" << std::endl;
                    }
                }
            } catch (const std::exception &e) {
                std::cerr << "Error while loading system: " << e.what() << std::endl;
                // Handle the error in another way if needed
            }
        }
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

        void RunSystems(sol::state &lua)
        {
            for (const auto &pair : m_systems) {
                const auto &system = pair.second;
                system->run(lua);
            }
        }

    private:
        std::unordered_map<const char *, Signature> m_signatures {};
        std::unordered_map<const char *, std::shared_ptr<ISystem>> m_systems {};
    };

} // namespace RType::Runtime::ECS
