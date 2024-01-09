/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** RType
*/

#pragma once

#include <any>
#include <cctype>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#ifdef __APPLE__
    #include <sstream>
#endif

#include "Utils/Logger.hpp"
#include "Modules/modules.hpp"
#include "Runtime/AssetManager.hpp"
#include "Runtime/IRuntime.hpp"

#define RTYPE_VERSION_MAJOR "0"
#define RTYPE_VERSION_MINOR "2"
#define RTYPE_VERSION       RTYPE_VERSION_MAJOR "." RTYPE_VERSION_MINOR

#ifdef _WIN32
    #define RTYPE_EXPORT __declspec(dllexport)
#elif __GNUC__
    #define RTYPE_EXPORT __attribute__((visibility("default")))
#else
    #define RTYPE_EXPORT
#endif

#define INIT_FILE_LOG \
    RType::Utils::Logger::Init();

#define EDITOR_LOG_INFO(...)     RType::Utils::Logger::Get().info("[Editor]: " __VA_ARGS__)
#define EDITOR_LOG_WARN(...)     RType::Utils::Logger::Get().warn("[Editor]: " __VA_ARGS__)
#define EDITOR_LOG_ERROR(...)    RType::Utils::Logger::Get().error("[Editor]: " __VA_ARGS__)
#define EDITOR_LOG_CRITICAL(...) RType::Utils::Logger::Get().critical("[Editor]: " __VA_ARGS__)

#define RUNTIME_LOG_INFO(...)     RType::Utils::Logger::Get().info("[Runtime]: " __VA_ARGS__)
#define RUNTIME_LOG_WARN(...)     RType::Utils::Logger::Get().warn("[Runtime]: " __VA_ARGS__)
#define RUNTIME_LOG_ERROR(...)    RType::Utils::Logger::Get().error("[Runtime]: " __VA_ARGS__)
#define RUNTIME_LOG_CRITICAL(...) RType::Utils::Logger::Get().critical("[Runtime]: " __VA_ARGS__)

#define NETWORK_LOG_INFO(...)     RType::Utils::Logger::Get().info("[Network]: " __VA_ARGS__)
#define NETWORK_LOG_WARN(...)     RType::Utils::Logger::Get().warn("[Network]: " __VA_ARGS__)
#define NETWORK_LOG_ERROR(...)    RType::Utils::Logger::Get().error("[Network]: " __VA_ARGS__)
#define NETWORK_LOG_CRITICAL(...) RType::Utils::Logger::Get().critical("[Network]: " __VA_ARGS__)

#define SERVER_LOG_INFO(...)     RType::Utils::Logger::Get().info("[Server]: " __VA_ARGS__)
#define SERVER_LOG_WARN(...)     RType::Utils::Logger::Get().warn("[Server]: " __VA_ARGS__)
#define SERVER_LOG_ERROR(...)    RType::Utils::Logger::Get().error("[Server]: " __VA_ARGS__)
#define SERVER_LOG_CRITICAL(...) RType::Utils::Logger::Get().critical("[Server]: " __VA_ARGS__)

#define RTYPE_LOG_INFO(...)     RType::Utils::Logger::Get().info("[RType]: " __VA_ARGS__)
#define RTYPE_LOG_WARN(...)     RType::Utils::Logger::Get().warn("[RType]: " __VA_ARGS__)
#define RTYPE_LOG_ERROR(...)    RType::Utils::Logger::Get().error("[RType]: " __VA_ARGS__)
#define RTYPE_LOG_CRITICAL(...) RType::Utils::Logger::Get().critical("[RType]: " __VA_ARGS__)

#define CLIENT_LOG_INFO(...)     RType::Utils::Logger::Get().info("[Client]: " __VA_ARGS__)
#define CLIENT_LOG_WARN(...)     RType::Utils::Logger::Get().warn("[Client]: " __VA_ARGS__)
#define CLIENT_LOG_ERROR(...)    RType::Utils::Logger::Get().error("[Client]: " __VA_ARGS__)
#define CLIENT_LOG_CRITICAL(...) RType::Utils::Logger::Get().critical("[Client]: " __VA_ARGS__)

#define ASSERT(x, ...)                                         \
    if (!(x)) {                                                \
        RTYPE_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
        exit(84);                                              \
    }

#define ASSERT_CONDITION(x, y, ...)                            \
    if (x != y) {                                              \
        RTYPE_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
        exit(84);                                              \
    }

#define BIT(x) (1 << x)

#define SKIP_EXCEPTIONS(x) \
    try {                  \
        x;                 \
    } catch (...) {        \
    }
