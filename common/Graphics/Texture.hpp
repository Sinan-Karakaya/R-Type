/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Texture
*/

#pragma once

#include "Utils.hpp"
#include <string>

namespace RType::Graphics
{
    class Texture
    {
    public:
        Texture() = default;
        Texture(const Texture &texture) = default;
        virtual ~Texture() = default;

        virtual bool create(uint32_t width, uint32_t height) = 0;
        virtual bool loadFromFile(const std::string &filename, const IntRect &area = IntRect()) = 0;

        virtual Vector2u getSize() const = 0;
        // virtual void update(const Texture &texture) = 0;

        virtual void setSmooth(bool smooth) = 0;
        virtual bool isSmooth() const = 0;

        virtual void setRepeated(bool repeated) = 0;
        virtual bool isRepeated() const = 0;

        virtual void *getTexture() const = 0;
    };
} // namespace RType::Graphics
