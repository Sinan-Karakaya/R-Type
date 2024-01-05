/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** KeyBoardSFML
*/

#pragma once

#include "Graphics/Keyboard.hpp"
#include <SFML/Window/Keyboard.hpp>

namespace RType::Graphics
{
    class KeyBoardSFML : public Keyboard {
        public:
            KeyBoardSFML();
            ~KeyBoardSFML();

            bool IsKeyPressed(Key key) override;
            bool IsKeyPressed(Scancode key) override;

        public:
            sf::Keyboard keyboard;
    };
} // namespace RType::Graphics
