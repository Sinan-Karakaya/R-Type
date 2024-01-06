/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** ColorSFML
*/

#pragma once

#include "Graphics/Color.hpp"
#include <SFML/Graphics/Color.hpp>

namespace RType::Graphics
{
    class ColorSFML : public Color
    {
    public:
        ColorSFML();
        ColorSFML(const Color &copy);
        ColorSFML(const ColorSFML &copy);
        ColorSFML(const sf::Color &color);
        ColorSFML(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
        ~ColorSFML();

        uint8_t GetR() const;
        uint8_t GetG() const;
        uint8_t GetB() const;
        uint8_t GetA() const;

    public:
        sf::Color color;
    };

    /*
    Color &operator==(const Color &lhs, const Color &rhs);
    Color &operator!=(const Color &lhs, const Color &rhs);
    Color &operator+(const Color &lhs, const Color &rhs);
    Color &operator+=(const Color &lhs, const Color &rhs);
    Color &operator-(const Color &lhs, const Color &rhs);
    Color &operator-=(const Color &lhs, const Color &rhs);
    Color &operator*(const Color &lhs, const Color &rhs);
    Color &operator*=(const Color &lhs, const Color &rhs);
    Color &operator/(const Color &lhs, const Color &rhs);
    Color &operator/=(const Color &lhs, const Color &rhs);
    */

} // namespace RType::Graphics
