/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** CircleShapeSFML
*/

#include "CircleShapeSFML.hpp"

namespace RType::Graphics
{
    CircleShapeSFML::CircleShapeSFML()
    {
        m_circle = sf::CircleShape();
    }

    CircleShapeSFML::~CircleShapeSFML() {}

    void CircleShapeSFML::setRadius(float radius)
    {
        m_circle.setRadius(radius);
    }

    float CircleShapeSFML::getRadius() const
    {
        return m_circle.getRadius();
    }

    void CircleShapeSFML::setPointCount(uint32_t count)
    {
        m_circle.setPointCount(count);
    }

    uint32_t CircleShapeSFML::getPointCount() const
    {
        return m_circle.getPointCount();
    }
} // namespace RType::Graphics
