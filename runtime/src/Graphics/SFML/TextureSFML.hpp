/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** TextureSFML
*/

#pragma once

#include "Graphics/Texture.hpp"
#include <SFML/Graphics/Texture.hpp>

namespace RType::Graphics
{
    class TextureSFML : public Texture
    {
    public:
        TextureSFML();
        TextureSFML(const sf::Texture &texture);
        TextureSFML(const Texture &texture);
        ~TextureSFML();

        bool create(uint32_t width, uint32_t height);
        bool loadFromFile(const std::string &filename, const IntRect &area = IntRect());

        Vector2u getSize() const;
        // void update(const Texture &texture);

        void setSmooth(bool smooth);
        bool isSmooth() const;

        void setRepeated(bool repeated);
        bool isRepeated() const;

        void *getTexture() const override;

    public:
        sf::Texture texture;
    };
} // namespace RType::Graphics
