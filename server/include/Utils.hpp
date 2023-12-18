/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Utils
*/

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <chrono>

namespace RType::Server
{
    class Utils
    {
    public:
        static long getCurrentTimeMillis()
        {
            return std::chrono::duration_cast<std::chrono::milliseconds>(
                       std::chrono::system_clock::now().time_since_epoch())
                .count();
        }
    };
} // namespace RType::Server

#endif /* !UTILS_HPP_ */
