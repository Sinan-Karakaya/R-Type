/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Mouse
*/

#pragma once

namespace RType::Graphics
{
    class Mouse
    {
    public:
        enum Button {
            Left,
            Right,
            Middle,
            XButton1,
            XButton2,
            ButtonCount
        };

        enum Wheel {
            VerticalWheel,
            HorizontalWheel
        };

        virtual bool isButtonPressed(Button button) = 0;

        virtual int getX() = 0;
        virtual int getY() = 0;

        virtual void setPosition(int x, int y) = 0;
    };
} // namespace RType::Graphics
