/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Sprite
*/

#pragma once

#include "Color.hpp"
#include "Texture.hpp"

namespace RType::Graphics
{
    class Sprite
    {
    public:
        Sprite();
        Sprite(const Texture &texture);
        Sprite(const Texture &texture, const IntRect &rectangle);

        virtual void setTexture(const Texture &texture, bool resetRect = false) = 0;
        virtual void setTextureRect(const IntRect &rectangle) = 0;
        virtual void setColor(const Color &color) = 0;

        virtual const Texture *getTexture() const = 0;
        virtual const IntRect &getTextureRect() const = 0;
        virtual const Color &getColor() const = 0;
        virtual const FloatRect &getLocalBounds() const = 0;
        virtual const FloatRect &getGlobalBounds() const = 0;
    };
} // namespace RType::Graphics
