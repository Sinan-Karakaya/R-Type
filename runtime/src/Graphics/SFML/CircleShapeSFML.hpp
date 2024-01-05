/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** CircleShapeSFML
*/

#pragma once

#include "Graphics/CircleShape.hpp"
#include <SFML/Graphics/CircleShape.hpp>

namespace RType::Graphics
{
    class CircleShapeSFML : public CircleShape
    {
    public:
        CircleShapeSFML();
        ~CircleShapeSFML();

        void setRadius(float radius) override;
        float getRadius() const override;

        void setPointCount(uint32_t count) override;
        uint32_t getPointCount() const override;

    private:
        sf::CircleShape m_circle;
    };
} // namespace RType::Graphics
