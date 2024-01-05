/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Color
*/

#pragma once

#include <cstdint>

namespace RType::Graphics
{
    class Color
    {
    public:
        Color();
        Color(const Color &copy);
        Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
        ~Color();

        virtual uint8_t GetR() const { return r; };
        virtual uint8_t GetG() const { return g; };
        virtual uint8_t GetB() const { return b; };
        virtual uint8_t GetA() const { return a; };

    public:
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };

} // namespace RType::Graphics
