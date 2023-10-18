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

#define RTYPE_VERSION_MAJOR 0
#define RTYPE_VERSION_MINOR 1

#define ENGINE_LOG_INFO(...)     spdlog::info("[Engine]: " __VA_ARGS__)
#define ENGINE_LOG_WARN(...)     spdlog::warn("[Engine]: " __VA_ARGS__)
#define ENGINE_LOG_ERROR(...)    spdlog::error("[Engine]: " __VA_ARGS__)
#define ENGINE_LOG_CRITICAL(...) spdlog::critical("[Engine]: " __VA_ARGS__)

#define RTYPE_LOG_INFO(...)     spdlog::info("[RType]: " __VA_ARGS__)
#define RTYPE_LOG_WARN(...)     spdlog::warn("[RType]: " __VA_ARGS__)
#define RTYPE_LOG_ERROR(...)    spdlog::error("[RType]: " __VA_ARGS__)
#define RTYPE_LOG_CRITICAL(...) spdlog::critical("[RType]: " __VA_ARGS__)

#define ASSERT(x, ...)                                          \
    if (!(x)) {                                                 \
        ENGINE_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
        __debugbreak();                                         \
    }

#define ASSERT_CONDITION(x, y, ...)                             \
    if (x != y) {                                               \
        ENGINE_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
        __debugbreak();                                         \
    }

#define BIT(x) (1 << x)
