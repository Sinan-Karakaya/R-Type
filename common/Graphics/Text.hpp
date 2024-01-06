/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Text
*/

#pragma once

#include "Color.hpp"
#include "Font.hpp"
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

        Text() = default;
        Text(const std::string &string, const Font &font, uint32_t characterSize = 30)
        {
            setString(string);
            setFont(font);
            setCharacterSize(characterSize);
        }
        virtual ~Text() = default;

        virtual void setString(const std::string &string) = 0;
        virtual void setFont(const Font &font) = 0;
        virtual void setCharacterSize(uint32_t size) = 0;
        virtual void setLineSpacing(uint32_t spacingFactor) = 0;
        virtual void setStyle(Style style) = 0;
        virtual void setFillColor(const Color &color) = 0;
        virtual void setOutlineColor(const Color &color) = 0;
        virtual void setOutlineThickness(float thickness) = 0;
        virtual void setLetterSpacing(float spacingFactor) = 0;

        virtual const std::string getString() const = 0;
        // virtual const Font &getFont() const = 0;
        virtual uint32_t getCharacterSize() const = 0;
        virtual uint32_t getLineSpacing() const = 0;
        virtual Style getStyle() const = 0;
        virtual const Color getFillColor() const = 0;
        virtual const Color getOutlineColor() const = 0;
        virtual float getOutlineThickness() const = 0;
        virtual float getLetterSpacing() const = 0;

        virtual const FloatRect getLocalBounds() const = 0;
        virtual const FloatRect getGlobalBounds() const = 0;
    };

    typedef Text::Style Style;
} // namespace RType::Graphics
