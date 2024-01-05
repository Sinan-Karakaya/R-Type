/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** FontSFML
*/

#include "FontSFML.hpp"

namespace RType::Graphics
{
    FontSFML::FontSFML()
    {
        font = sf::Font();
    }

    FontSFML::FontSFML(sf::Font font)
    {
        this->font = font;
    }

    FontSFML::FontSFML(const FontSFML &font) : font(font.font)
    {
        this->font = font.font;
    }

    FontSFML::~FontSFML() {}

    bool FontSFML::loadFromFile(const std::string &filename)
    {
        return font.loadFromFile(filename);
    }

    void FontSFML::setSmooth(bool smooth)
    {
        font.setSmooth(smooth);
    }

    bool FontSFML::isSmooth() const
    {
        return font.isSmooth();
    }

    void *FontSFML::getFont() const
    {
        return (void *)&font;
    }
} // namespace RType::Graphics
