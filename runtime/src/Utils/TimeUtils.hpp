/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** TimeUtils
*/

#ifndef TIMEUTILS_HPP_
#define TIMEUTILS_HPP_

#include <chrono>

namespace RType::Utils
{
    class TimeUtils {
    public:
        static long getCurrentTimeMillis()
        {
            return std::chrono::duration_cast<std::chrono::milliseconds>(
                       std::chrono::system_clock::now().time_since_epoch())
                .count();
        }
    };
} // namespace RType::Utils


#endif /* !TIMEUTILS_HPP_ */
