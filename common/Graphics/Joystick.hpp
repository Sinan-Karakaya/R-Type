/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Joystick
*/

#ifndef JOYSTICK_HPP_
#define JOYSTICK_HPP_

class Joystick {
    public:

        enum {
            Count = 8, // Maximum number of supported joysticks
            ButtonCount = 32, // Maximum number of supported buttons
            AxisCount = 8, // Maximum number of supported axes
        };

        enum Axis {
            X, // The X axis
            Y, // The Y axis
            Z, // The Z axis
            R, // The R axis
            U, // The U axis
            V, // The V axis
            PovX, // The X axis of the point-of-view hat
            PovY, // The Y axis of the point-of-view hat
        };

        virtual bool isConnected(uint32_t joystick) = 0;
        virtual uint32_t getButtonCount(uint32_t joystick) = 0;
        virtual bool hasAxis(uint32_t joystick, Axis axis) = 0;
        virtual bool isButtonPressed(uint32_t joystick, uint32_t button) = 0;
        virtual float getAxisPosition(uint32_t joystick, Axis axis) = 0;
        virtual void update() = 0;
};

#endif /* !JOYSTICK_HPP_ */
