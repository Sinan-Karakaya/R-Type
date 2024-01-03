/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** RectangleShape
*/

#pragma once

#include "Utils.hpp"

namespace RType::Graphics
{
    class RectangleShape
    {
    public:
        RectangleShape();
        RectangleShape(const Vector2f &size = Vector2f(0, 0));
        ~RectangleShape();

        virtual void setSize(const Vector2f &size);
        virtual const Vector2f &getSize() const;
        virtual Vector2f getPoint(std::size_t index) const;
    };
} // namespace RType::Graphics
