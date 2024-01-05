/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** RectangleShapeSFML
*/

#pragma once

#include "Graphics/RectangleShape.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

namespace RType::Graphics
{
    class RectangleShapeSFML : RType::Graphics::RectangleShape
    {
    public:
        RectangleShapeSFML();
        ~RectangleShapeSFML();

        void setSize(const Vector2f &size) override;
        const Vector2f &getSize() const override;
        Vector2f getPoint(std::size_t index) const override;

    public:
        sf::RectangleShape m_rectangleShape;
    };
} // namespace RType::Graphics
