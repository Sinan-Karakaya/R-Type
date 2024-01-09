/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Logger
*/

#pragma once

#include <memory>
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/spdlog.h"

namespace RType::Utils
{

    class Logger
    {
    public:
        static void Init(const std::string &filename = "./logs/RType.log")
        {
            constexpr const uint32_t maxFileSize = 1024 * 1024 * 5;
            constexpr const uint32_t maxFileCount = 3;

            m_logger = spdlog::rotating_logger_mt("RType", filename, maxFileSize, maxFileCount);
        }

        static spdlog::logger &Get() { return *m_logger; }

    private:
        inline static std::shared_ptr<spdlog::logger> m_logger;
    };

} // namespace RType::Utils
