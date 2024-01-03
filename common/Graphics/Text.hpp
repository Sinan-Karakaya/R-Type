/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Text
*/

#pragma once

#include "Font.hpp"

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

        void setString(const std::string &string);
        void setFont(const Font &font);
        void setCharacterSize(uint32_t size);
        void setLineSpacing(uint32_t spacingFactor);
        void setStyle(Style style);
        void setFillColor(const Color &color);
        void setOutlineColor(const Color &color);
        void setOutlineThickness(float thickness);
        void setLetterSpacing(float spacingFactor);

        const std::string &getString() const;
        const Font &getFont() const;
        uint32_t getCharacterSize() const;
        uint32_t getLineSpacing() const;
        Style getStyle() const;
        const Color &getFillColor() const;
        const Color &getOutlineColor() const;
        float getOutlineThickness() const;
        float getLetterSpacing() const;

        FloatRect getLocalBounds() const;
        FloatRect getGlobalBounds() const;
    };
} // namespace RType::Graphics
