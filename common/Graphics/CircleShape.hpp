/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** CircleShape
*/

#pragma once

#include <cstdint>

namespace RType::Graphics
{
    class CircleShape
    {
    public:
        // CircleShape(float radius = 0, uint32_t pointCount = 30);
        virtual ~CircleShape() = default;

        virtual void setRadius(float radius) = 0;
        virtual float getRadius() const = 0;

        virtual void setPointCount(uint32_t count) = 0;
        virtual uint32_t getPointCount() const = 0;
    };
} // namespace RType::Graphics
