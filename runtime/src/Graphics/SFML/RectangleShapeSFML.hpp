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
    class RectangleShapeSFML : public RectangleShape
    {
    public:
        RectangleShapeSFML();
        RectangleShapeSFML(const Vector2f &size);
        ~RectangleShapeSFML() = default;

        void setSize(const Vector2f &size) override;
        const Vector2f getSize() const override;
        const Vector2f getPoint(std::size_t index) const override;

    private:
        sf::RectangleShape m_rectangleShape;
    };
} // namespace RType::Graphics