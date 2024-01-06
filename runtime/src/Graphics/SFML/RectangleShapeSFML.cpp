/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** RectangleShapeSFML
*/

#include "RectangleShapeSFML.hpp"

namespace RType::Graphics
{
    RectangleShapeSFML::RectangleShapeSFML()
    {

    }

    RectangleShapeSFML::RectangleShapeSFML(const Vector2f &size)
    {
        m_rectangleShape.setSize({size.x, size.y});
    }

    void RectangleShapeSFML::setSize(const Vector2f &size)
    {
        m_rectangleShape.setSize({size.x, size.y});
    }

    const Vector2f RectangleShapeSFML::getSize() const
    {
        sf::Vector2f size = m_rectangleShape.getSize();
        return {size.x, size.y};
    }

    const Vector2f RectangleShapeSFML::getPoint(std::size_t index) const
    {
        return {m_rectangleShape.getPoint(index).x,
                m_rectangleShape.getPoint(index).y};
    }
} // namespace RType::Graphics
