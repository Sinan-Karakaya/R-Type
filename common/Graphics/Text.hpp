/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Text
*/

#pragma once

#include "Font.hpp"
#include "Color.hpp"
#include "Utils.hpp"
#include <string>

namespace RType::Graphics
{
    class Text
    {
    public:
        enum Style {
            Regular = 0,
            Bold = 1 << 0,
            Italic = 1 << 1,
            Underlined = 1 << 2,
            StrikeThrough = 1 << 3
        };

        Text();
        Text(const std::string &string, const Font &font, uint32_t characterSize = 30);

        virtual void setString(const std::string &string);
        virtual void setFont(const Font &font);
        virtual void setCharacterSize(uint32_t size);
        virtual void setLineSpacing(uint32_t spacingFactor);
        virtual void setStyle(Style style);
        virtual void setFillColor(const Color &color);
        virtual void setOutlineColor(const Color &color);
        virtual void setOutlineThickness(float thickness);
        virtual void setLetterSpacing(float spacingFactor);

        virtual const std::string &getString() const;
        virtual const Font &getFont() const;
        virtual uint32_t getCharacterSize() const;
        virtual uint32_t getLineSpacing() const;
        virtual Style getStyle() const;
        virtual const Color &getFillColor() const;
        virtual const Color &getOutlineColor() const;
        virtual float getOutlineThickness() const;
        virtual float getLetterSpacing() const;

        virtual const FloatRect getLocalBounds() const;
        virtual const FloatRect getGlobalBounds() const;

    };

    typedef Text::Style Style;
} // namespace RType::Graphics
