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
        static bool ExecFunction(sol::state &lua, const std::string &scriptPath, const std::string &functionName,
                                 Args &&...args)
        {
            if (scriptPath.empty() || !scriptPath.ends_with(".lua")) {
                return false;
            }
            if (!std::filesystem::exists(scriptPath)) {
                return false;
            }

            std::string script_content = AssetManager::getScript(scriptPath);
            if (script_content.empty()) {
                return false;
            }
            lua.safe_script(script_content);

            sol::protected_function f = lua[functionName];
            if (!f.valid())
                return false;
            sol::protected_function_result res = f(std::forward<Args>(args)...);
            if (!res.valid()) {
                sol::error err = res;
                RTYPE_LOG_ERROR("{0} - {1}: {2}", scriptPath, functionName, err.what());
            }
            return true;
        }

        template <typename... Args>
        static void ExecFunctionOnCurrentLoadedScript(sol::state &lua, const std::string &path,
                                                      const std::string &functionName, Args &&...args)
        {
            sol::protected_function f = lua[functionName];

            if (!f.valid())
                return;
            sol::protected_function_result res = f(std::forward<Args>(args)...);
            if (!res.valid()) {
                sol::error err = res;
                RTYPE_LOG_ERROR("{0} - {1}: {2}", path, functionName, err.what());
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
