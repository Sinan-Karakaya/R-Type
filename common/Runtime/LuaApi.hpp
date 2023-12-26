/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** LuaApi
*/

#ifndef LUAAPI_HPP_
#define LUAAPI_HPP_

#define SOL_ALL_SAFETIES_ON 1

#include "RType.hpp"

namespace RType::Runtime
{
    class LuaApi
    {
    public:
        template <typename... Args>
        static void ExecFunction(sol::state &lua, const std::string &scriptPath, const std::string &functionName,
                                 Args &&...args)
        {
            if (scriptPath.empty() || !scriptPath.ends_with(".lua")) {
                return;
            }
            if (!std::filesystem::exists(scriptPath)) {
                return;
            }

            std::string script_content = AssetManager::getScript(scriptPath);
            lua.script(script_content);
            sol::function f = lua[functionName];

            if (!f.valid())
                return;
            sol::protected_function_result res = f(std::forward<Args>(args)...);
            if (!res.valid()) {
                sol::error err = res;
                RTYPE_LOG_ERROR("{0}: {1}", scriptPath, err.what());
            }
        }

        template<typename... Args>
        static void ExecFunctionOnCurrentLoadedScript(sol::state &lua, const std::string &path, const std::string &functionName, Args&&...args)
        {
            sol::function f = lua[functionName];

            if (!f.valid())
                return;
            sol::protected_function_result res = f(std::forward<Args>(args)...);
            if (!res.valid()) {
                sol::error err = res;
                RTYPE_LOG_ERROR("{0}: {1}", path, err.what());
            }
        }

        static std::string GetScriptPath(const std::string &projectPath, const std::string &scriptName)
        {
            std::string scriptPath = projectPath + "/assets/scripts/" + scriptName;
            return scriptPath;
        }
    };
} // namespace RType::Runtime

#endif /* !LUAAPI_HPP_ */
