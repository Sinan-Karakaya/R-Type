/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Logger
*/

#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include "spdlog/spdlog.h"

#define NETWORK_LOG_INFO(...)     spdlog::info("[Network]: " __VA_ARGS__)
#define NETWORK_LOG_WARN(...)     spdlog::warn("[Network]: " __VA_ARGS__)
#define NETWORK_LOG_ERROR(...)    spdlog::error("[Network]: " __VA_ARGS__)
#define NETWORK_LOG_CRITICAL(...) spdlog::critical("[Network]: " __VA_ARGS__)

#endif /* !LOGGER_HPP_ */
