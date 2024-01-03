/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Color
*/

#pragma once

namespace RType::Graphics
{
    class Color
    {
    public:
        Color();
        Color(const Color &copy);
        Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
        ~Color();
    };

    virtual Color &operator==(const Color &lhs, const Color &rhs);
    virtual Color &operator!=(const Color &lhs, const Color &rhs);
    virtual Color &operator+(const Color &lhs, const Color &rhs);
    virtual Color &operator+=(const Color &lhs, const Color &rhs);
    virtual Color &operator-(const Color &lhs, const Color &rhs);
    virtual Color &operator-=(const Color &lhs, const Color &rhs);
    virtual Color &operator*(const Color &lhs, const Color &rhs);
    virtual Color &operator*=(const Color &lhs, const Color &rhs);
    virtual Color &operator/(const Color &lhs, const Color &rhs);
    virtual Color &operator/=(const Color &lhs, const Color &rhs);

} // namespace RType::Graphics
