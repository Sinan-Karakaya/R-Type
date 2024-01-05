/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** TextSFML
*/

#include "TextSFML.hpp"

namespace RType::Graphics
{
    TextSFML::TextSFML() {}

    TextSFML::TextSFML(const std::string &string, const Font &font, uint32_t characterSize)
    {
        text.setString(string);
        text.setFont(*(sf::Font *)font.getFont());
        text.setCharacterSize(characterSize);
    }

    void TextSFML::setString(const std::string &string)
    {
        text.setString(string);
    }

    void TextSFML::setFont(const Font &font)
    {
        text.setFont(*(sf::Font *)font.getFont());
    }

    void TextSFML::setCharacterSize(uint32_t size)
    {
        text.setCharacterSize(size);
    };

    void TextSFML::setLineSpacing(uint32_t spacingFactor)
    {
        text.setLineSpacing(spacingFactor);
    };

    // TODO: check if Style is compatible with sf::Uint32
    void TextSFML::setStyle(Style style)
    {
        text.setStyle((sf::Uint32)style);
    };

    void TextSFML::setFillColor(const Color &color)
    {
        text.setFillColor(sf::Color(color.GetR(), color.GetG(), color.GetB(), color.GetA()));
    };

    void TextSFML::setOutlineColor(const Color &color)
    {
        text.setOutlineColor(sf::Color(color.GetR(), color.GetG(), color.GetB(), color.GetA()));
    };

    void TextSFML::setOutlineThickness(float thickness)
    {
        text.setOutlineThickness(thickness);
    };

    void TextSFML::setLetterSpacing(float spacingFactor)
    {
        text.setLetterSpacing(spacingFactor);
    }

    const std::string &TextSFML::getString() const
    {
        // return text.getString();
    }

    const Font &TextSFML::getFont() const
    {
        // same problem as Color
        // return text.getFont();
    }

    uint32_t TextSFML::getCharacterSize() const
    {
        return text.getCharacterSize();
    }

    uint32_t TextSFML::getLineSpacing() const
    {
        return text.getLineSpacing();
    }

    Style TextSFML::getStyle() const
    {
        return (Style)text.getStyle();
    }

    const Color &TextSFML::getFillColor() const
    {
        // sf::Color color = text.getFillColor();
        // return Color(color.r, color.g, color.b, color.a);
    }

    const Color &TextSFML::getOutlineColor() const
    {
        // sf::Color color = text.getOutlineColor();
        // return Color(color.r, color.g, color.b, color.a);
    }

    float TextSFML::getOutlineThickness() const
    {
        return text.getOutlineThickness();
    }

    float TextSFML::getLetterSpacing() const
    {
        return text.getLetterSpacing();
    }

    const FloatRect TextSFML::getLocalBounds() const
    {
        // get sf::FloatRect and then retur a FloatRect
        sf::FloatRect rect = text.getLocalBounds();
        return FloatRect(rect.left, rect.top, rect.width, rect.height);
    }

    const FloatRect TextSFML::getGlobalBounds() const
    {
        sf::FloatRect rect = text.getGlobalBounds();
        return FloatRect(rect.left, rect.top, rect.width, rect.height);
    }

} // namespace RType::Graphics
