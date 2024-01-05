/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** JoystickSFML
*/

#pragma once

#include "Graphics/Joystick.hpp"
#include <SFML/Window/Joystick.hpp>

namespace RType::Graphics
{
    class JoystickSFML : public Joystick
    {
    public:
        JoystickSFML();
        ~JoystickSFML();

        bool isConnected(uint32_t joystick) override;
        uint32_t getButtonCount(uint32_t joystick) override;
        bool hasAxis(uint32_t joystick, Axis axis) override;
        bool isButtonPressed(uint32_t joystick, uint32_t button) override;
        float getAxisPosition(uint32_t joystick, Axis axis) override;
        void update() override;

    public:
        sf::Joystick joystick;
    };
} // namespace RType::Graphics
