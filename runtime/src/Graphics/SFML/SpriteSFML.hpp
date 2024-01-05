/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** SpriteSFML
*/

#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include "Graphics/Sprite.hpp"
#include "Graphics/Color.hpp"

#include "TextureSFML.hpp"

namespace RType::Graphics
{
    class SpriteSFML : public Sprite {
        public:
            SpriteSFML();
            SpriteSFML(const TextureSFML &texture);
            SpriteSFML(const TextureSFML &texture, const IntRect &rectangle);

            void setTexture(const Texture &texture, bool resetRect = false) override;
            void setTextureRect(const IntRect &rectangle) override;
            void setColor(const Color &color) override;

            const Texture *getTexture() const override;
            const IntRect &getTextureRect() const override;
            const Color &getColor() const override;
            const FloatRect &getLocalBounds() const override;
            const FloatRect &getGlobalBounds() const override;

        public:
            sf::Sprite sprite;
    };
} // namespace RType::Graphics
