/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Logger
*/

#pragma once

#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/spdlog.h"
#include <memory>

#include "Uuid.hpp"

namespace RType::Utils
{

    class Logger
    {
    public:
        static void Init(const std::string &filename = "./logs/RType.log")
        {
            m_logger =
                spdlog::rotating_logger_mt(RType::Utils::UUIDS::generate().c_str(), filename, 1024 * 1024 * 5, 3);
        }

        static spdlog::logger &Get() {
            return *m_logger;
        }

    private:
        inline static std::shared_ptr<spdlog::logger> m_logger = nullptr;
    };

} // namespace RType::Utils
