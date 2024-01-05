/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** MouseSFML
*/

#include "MouseSFML.hpp"

namespace RType::Graphics
{
    MouseSFML::MouseSFML() {}

    MouseSFML::~MouseSFML() {}

    bool MouseSFML::isButtonPressed(Button button)
    {
        return mouse.isButtonPressed(sf::Mouse::Button(button));
    }

    int MouseSFML::getX()
    {
        return mouse.getPosition().x;
    }

    int MouseSFML::getY()
    {
        return mouse.getPosition().y;
    }

    void MouseSFML::setPosition(int x, int y)
    {
        mouse.setPosition(sf::Vector2i(x, y));
    }

} // namespace RType::Graphics
