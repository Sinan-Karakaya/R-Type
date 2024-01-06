/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** ColorSFML
*/

#include "ColorSFML.hpp"

namespace RType::Graphics
{
    ColorSFML::ColorSFML()
    {
        color = sf::Color();
    }

    ColorSFML::ColorSFML(const sf::Color &color)
    {
        this->color = color;
    }

    ColorSFML::ColorSFML(const Color &copy)
    {
        color = sf::Color(copy.GetR(), copy.GetG(), copy.GetG(), copy.GetA());
    }

    ColorSFML::ColorSFML(const ColorSFML &copy) : Color(copy)
    {
        color = sf::Color(copy.color.r, copy.color.g, copy.color.b, copy.color.a);
    }

    ColorSFML::ColorSFML(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        color = sf::Color(r, g, b, a);
    }

    ColorSFML::~ColorSFML() {}

    uint8_t ColorSFML::GetR() const
    {
        return color.r;
    }

    uint8_t ColorSFML::GetG() const
    {
        return color.g;
    }

    uint8_t ColorSFML::GetB() const
    {
        return color.b;
    }

    uint8_t ColorSFML::GetA() const
    {
        return color.a;
    }

    /*
    bool operator==(const ColorSFML &lhs, const ColorSFML &rhs)
    {
        return lhs.color.r == rhs.color.r && lhs.color.g == rhs.color.g &&
               lhs.color.b == rhs.color.b && lhs.color.a == rhs.color.a;
    }

    bool operator!=(const ColorSFML &lhs, const ColorSFML &rhs)
    {
        return lhs.color != rhs.color;
    }

    ColorSFML &operator+(const ColorSFML &lhs, const ColorSFML &rhs)
    {
        return lhs.color + rhs.color;
    }

    ColorSFML &operator+=(const ColorSFML &lhs, const ColorSFML &rhs)
    {
        return lhs.color += rhs.color;
    }

    ColorSFML &operator-(const ColorSFML &lhs, const ColorSFML &rhs)
    {
        return lhs.color - rhs.color;
    }

    ColorSFML &operator-=(const ColorSFML &lhs, const ColorSFML &rhs)
    {
        return lhs.color -= rhs.color;
    }

    ColorSFML &operator*(const ColorSFML &lhs, const ColorSFML &rhs)
    {
        return lhs.color * rhs.color;
    }

    ColorSFML &operator*=(const ColorSFML &lhs, const ColorSFML &rhs)
    {
        return lhs.color *= rhs.color;
    }

    ColorSFML &operator/(const ColorSFML &lhs, const ColorSFML &rhs)
    {
        return lhs.color / rhs.color;
    }

    ColorSFML &operator/=(const ColorSFML &lhs, const ColorSFML &rhs)
    {
        return lhs.color /= rhs.color;
    }
    */

} // namespace RType::Graphics
