/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** KeyBoardSFML
*/

#include "KeyBoardSFML.hpp"

namespace RType::Graphics
{
    KeyBoardSFML::KeyBoardSFML()
    {
    }

    KeyBoardSFML::~KeyBoardSFML()
    {
    }

    bool KeyBoardSFML::IsKeyPressed(Key key)
    {
        return keyboard.isKeyPressed((sf::Keyboard::Key)key);
    }

    bool KeyBoardSFML::IsKeyPressed(Scancode key)
    {
        return keyboard.isKeyPressed((sf::Keyboard::Key)key);
    }

} // namespace RType::Graphics
