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
        CircleShape(float radius = 0, uint32_t pointCount = 30);

        virtual void setRadius(float radius);
        virtual float getRadius() const;

        virtual void setPointCount(uint32_t count);
        virtual uint32_t getPointCount() const;
    };
} // namespace RType::Graphics
