#pragma once

#include <any>
#include <cstdint>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "spdlog/spdlog.h"

#include "Modules/modules.hpp"
#include "Runtime/IRuntime.hpp"

#define RTYPE_VERSION_MAJOR 0
#define RTYPE_VERSION_MINOR 1

#define EDITOR_LOG_INFO(...)     spdlog::info("[Editor]: " __VA_ARGS__)
#define EDITOR_LOG_WARN(...)     spdlog::warn("[Editor]: " __VA_ARGS__)
#define EDITOR_LOG_ERROR(...)    spdlog::error("[Editor]: " __VA_ARGS__)
#define EDITOR_LOG_CRITICAL(...) spdlog::critical("[Editor]: " __VA_ARGS__)

#define RUNTIME_LOG_INFO(...)     spdlog::info("[Runtime]: " __VA_ARGS__)
#define RUNTIME_LOG_WARN(...)     spdlog::warn("[Runtime]: " __VA_ARGS__)
#define RUNTIME_LOG_ERROR(...)    spdlog::error("[Runtime]: " __VA_ARGS__)
#define RUNTIME_LOG_CRITICAL(...) spdlog::critical("[Runtime]: " __VA_ARGS__)

#define RTYPE_LOG_INFO(...)     spdlog::info("[RType]: " __VA_ARGS__)
#define RTYPE_LOG_WARN(...)     spdlog::warn("[RType]: " __VA_ARGS__)
#define RTYPE_LOG_ERROR(...)    spdlog::error("[RType]: " __VA_ARGS__)
#define RTYPE_LOG_CRITICAL(...) spdlog::critical("[RType]: " __VA_ARGS__)

#define ASSERT(x, ...)                                          \
    if (!(x)) {                                                 \
        RTYPE_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
        exit(84);                                      \
    }

#define ASSERT_CONDITION(x, y, ...)                             \
    if (x != y) {                                               \
        RTYPE_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
        exit(84);                                      \
    }

#define BIT(x) (1 << x)
