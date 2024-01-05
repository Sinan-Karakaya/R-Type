/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** FontSFML
*/

#pragma once

#include "Graphics/Font.hpp"
#include <SFML/Graphics/Font.hpp>

namespace RType::Graphics
{
    class FontSFML : public Font
    {
    public:
        FontSFML();
        FontSFML(sf::Font font);
        FontSFML(const FontSFML &font);
        ~FontSFML();

        bool loadFromFile(const std::string &filename) override;
        void setSmooth(bool smooth) override;
        bool isSmooth() const override;
        void *getFont() const override;

    public:
        sf::Font font;
    };

} // namespace RType::Graphics
