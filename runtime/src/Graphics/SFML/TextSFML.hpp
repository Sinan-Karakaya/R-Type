/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** TextSFML
*/

#pragma once

#include <SFML/Graphics/Text.hpp>
#include "Graphics/Text.hpp"

namespace RType::Graphics
{
    class TextSFML : public Text{
        public:
            TextSFML();
            TextSFML(const std::string &string, const Font &font, uint32_t characterSize = 30);

            void setString(const std::string &string) override;
            void setFont(const Font &font) override;
            void setCharacterSize(uint32_t size) override;
            void setLineSpacing(uint32_t spacingFactor) override;
            void setStyle(Style style) override;
            void setFillColor(const Color &color) override;
            void setOutlineColor(const Color &color) override;
            void setOutlineThickness(float thickness) override;
            void setLetterSpacing(float spacingFactor) override;

            const std::string &getString() const override;
            const Font &getFont() const override;
            uint32_t getCharacterSize() const override;
            uint32_t getLineSpacing() const override;
            Style getStyle() const override;
            const Color &getFillColor() const override;
            const Color &getOutlineColor() const override;
            float getOutlineThickness() const override;
            float getLetterSpacing() const override;

            const FloatRect getLocalBounds() const override;
            const FloatRect getGlobalBounds() const override;

        public:
            sf::Text text;

            // std::string              m_string;              // String to display
            // const Font*         m_font;                // Font used to display the string
            // unsigned int        m_characterSize;       // Base size of characters, in pixels
            // float               m_letterSpacingFactor; // Spacing factor between letters
            // float               m_lineSpacingFactor;   // Spacing factor between lines
            // uint32_t              m_style;               // Text style (see Style enum)
            // Color               m_fillColor;           // Text fill color
            // Color               m_outlineColor;        // Text outline color
            // float               m_outlineThickness;    // Thickness of the text's outline
            // // mutable FloatRect   m_bounds;              // Bounding rectangle of the text (in local coordinates)
            // FloatRect   m_bounds;              // Bounding rectangle of the text (in local coordinates)
            // mutable bool        m_geometryNeedUpdate;  // Does the geometry need to be recomputed?
    };
} // namespace RType::Graphics
