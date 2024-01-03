/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Event
*/

#pragma once

#include "Joystick.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"

namespace RType::Graphics
{

    class Event
    {
    public:
        struct ResizeEvent {
            uint32_t width;
            uint32_t height;
        };

        struct KeyEvent {
            Keyboard::Scancode scancode;
            Keyboard::Key code;
            bool alt;
            bool ctrl;
            bool shift;
            bool system;
        };

        struct MouseMoveEvent {
            int x;
            int y;
        };

        struct MouseButtonEvent {
            int x;
            int y;
            Mouse::Button button;
        };

        struct MouseWheelEvent {
            int delta;
            int x;
            int y;
        };

        struct MouseWheelScrollEvent {
            Mouse::Wheel wheel;
            float delta;
            int x;
            int y;
        };

        struct JoystickConnectEvent {
            uint32_t joystickId;
        };

        struct JoystickMoveEvent {
            uint32_t joystickId;
            Joystick::Axis axis;
            float position;
        };

        struct JoystickButtonEvent {
            uint32_t joystickId;
            uint32_t button;
        };

        enum EventType {
            Closed,                 // The window requested to be closed (no data)
            Resized,                // The window was resized (data in event.size)
            LostFocus,              // The window lost the focus (no data)
            GainedFocus,            // The window gained the focus (no data)
            TextEntered,            // A character was entered (data in event.text)
            KeyPressed,             // A key was pressed (data in event.key)
            KeyReleased,            // A key was released (data in event.key)
            MouseWheelMoved,        // The mouse wheel was scrolled (data in event.mouseWheel) (deprecated)
            MouseWheelScrolled,     // The mouse wheel was scrolled (data in event.mouseWheelScroll)
            MouseButtonPressed,     // A mouse button was pressed (data in event.mouseButton)
            MouseButtonReleased,    // A mouse button was released (data in event.mouseButton)
            MouseMoved,             // The mouse cursor moved (data in event.mouseMove)
            MouseEntered,           // The mouse cursor entered the area of the window (no data)
            MouseLeft,              // The mouse cursor left the area of the window (no data)
            JoystickButtonPressed,  // A joystick button was pressed (data in event.joystickButton)
            JoystickButtonReleased, // A joystick button was released (data in event.joystickButton)
            JoystickMoved,          // The joystick moved along an axis (data in event.joystickMove)
            JoystickConnected,      // A joystick was connected (data in event.joystickConnect)
            JoystickDisconnected,   // A joystick was disconnected (data in event.joystickConnect)
            TouchBegan,             // A touch event began (data in event.touch)
            TouchMoved,             // A touch moved (data in event.touch)
            TouchEnded,             // A touch event ended (data in event.touch)
            SensorChanged,          // A sensor value changed (data in event.sensor)

            Count // Keep last -- the total number of event types
        };

        EventType type;

        union {
            ResizeEvent size;         // Size event parameters (Event::Resized)
            KeyEvent key;             // Key event parameters (Event::KeyPressed, Event::KeyReleased)
            MouseMoveEvent mouseMove; // Mouse move event parameters (Event::MouseMoved)
            MouseButtonEvent
                mouseButton; // Mouse button event parameters (Event::MouseButtonPressed, Event::MouseButtonReleased)
            MouseWheelEvent mouseWheel; // Mouse wheel event parameters (Event::MouseWheelMoved) (deprecated)
            MouseWheelScrollEvent mouseWheelScroll; // Mouse wheel event parameters (Event::MouseWheelScrolled)
            JoystickMoveEvent joystickMove;         // Joystick move event parameters (Event::JoystickMoved)
            JoystickButtonEvent joystickButton;     // Joystick button event parameters (Event::JoystickButtonPressed,
                                                    // Event::JoystickButtonReleased)
            JoystickConnectEvent joystickConnect;   // Joystick (dis)connect event parameters (Event::JoystickConnected,
                                                    // Event::JoystickDisconnected)
        };
    };
} // namespace RType::Graphics
