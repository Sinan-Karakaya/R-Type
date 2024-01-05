/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** IWindow
*/

#pragma once

#include "Event.hpp"

namespace RType::Graphics
{
    struct WindowProps {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowProps(const std::string &title = "R-Type editor", unsigned int width = 1920, unsigned int height = 1080)
            : Title(title), Width(width), Height(height)
        {
        }
    };

    class Window
    {
    public:
        using EventCallbackFn = std::function<void(RType::Graphics::Event &)>;

        Window(const WindowProps &props);
        ~Window();

        virtual void OnUpdate() = 0;

        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        // Window attributes
        virtual void SetEventCallback(const EventCallbackFn &callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        virtual void setFpsLimit(unsigned int fps) = 0;

        static Window *Create(const WindowProps &props = WindowProps());
    };
} // namespace RType::Graphics
