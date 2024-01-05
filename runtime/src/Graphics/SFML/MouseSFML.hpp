/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** MouseSFML
*/

#pragma once

#include "Graphics/Mouse.hpp"
#include <SFML/Window/Mouse.hpp>

namespace RType::Graphics
{
    class MouseSFML : public Mouse
    {
    public:
        MouseSFML();
        ~MouseSFML();

        bool isButtonPressed(Button button) override;

        int getX() override;
        int getY() override;

        void setPosition(int x, int y) override;

    public:
        sf::Mouse mouse;
    };
} // namespace RType::Graphics
