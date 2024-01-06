/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Sound
*/

#pragma once

#include <cstdint>
#include <string>

namespace RType::Graphics
{
    class SoundBuffer
    {
    public:
        SoundBuffer() = default;
        SoundBuffer(const SoundBuffer &copy) = default;
        virtual ~SoundBuffer() = default;

        virtual bool loadFromFile(const std::string &filename) = 0;
        virtual uint32_t getDuration() const = 0; // as milliseconds
    };
} // namespace RType::Graphics
