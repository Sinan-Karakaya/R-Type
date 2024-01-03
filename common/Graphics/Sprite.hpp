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
        Sprite(const Texture &texture) Sprite(const Texture &texture, const IntRect &rectangle)

            void setTexture(const Texture &texture, bool resetRect = false);
        void setTextureRect(const IntRect &rectangle);
        void setColor(const Color &color);

        const Texture *getTexture() const;
        const IntRect &getTextureRect() const;
        const Color &getColor() const;
        FloatRect getLocalBounds() const;
        FloatRect getGlobalBounds() const;
    };
} // namespace RType::Graphics
