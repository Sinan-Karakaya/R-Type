#include "JoystickSFML.hpp"
/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** JoystickSFML
*/

#include "JoystickSFML.hpp"

namespace RType::Graphics
{
    JoystickSFML::JoystickSFML()
    {
        joystick = sf::Joystick();
    }

    JoystickSFML::~JoystickSFML() {}

    bool RType::Graphics::JoystickSFML::isConnected(uint32_t joystick)
    {
        return this->joystick.isConnected(joystick);
    }

    uint32_t RType::Graphics::JoystickSFML::getButtonCount(uint32_t joystick)
    {
        return this->joystick.getButtonCount(joystick);
    }

    bool RType::Graphics::JoystickSFML::hasAxis(uint32_t joystick, Axis axis)
    {
        return this->joystick.hasAxis(joystick, (sf::Joystick::Axis)axis);
    }

    bool RType::Graphics::JoystickSFML::isButtonPressed(uint32_t joystick, uint32_t button)
    {
        return this->joystick.isButtonPressed(joystick, button);
    }

    float RType::Graphics::JoystickSFML::getAxisPosition(uint32_t joystick, Axis axis)
    {
        return this->joystick.getAxisPosition(joystick, (sf::Joystick::Axis)axis);
    }

    void RType::Graphics::JoystickSFML::update()
    {
        this->joystick.update();
    }

} // namespace RType::Graphics
