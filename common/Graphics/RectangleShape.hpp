/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** RectangleShape
*/

#pragma once

#include "Utils.hpp"
#include <cstddef>

namespace RType::Graphics
{
    class RectangleShape
    {
    public:
        RectangleShape() = default;
        RectangleShape(const Vector2f &size) { setSize(size); }
        virtual ~RectangleShape() = default;

        virtual void setSize(const Vector2f &size) = 0;
        virtual const Vector2f getSize() const = 0;
        virtual const Vector2f getPoint(std::size_t index) const = 0;
    };
} // namespace RType::Graphics
