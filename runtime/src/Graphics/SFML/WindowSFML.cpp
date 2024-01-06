/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** WindowSFML
*/

#include "WindowSFML.hpp"

namespace RType::Graphics
{
    WindowSFML *WindowSFML::Create(const WindowProps &props)
    {
        return new WindowSFML(props);
    }

    WindowSFML::WindowSFML(const WindowProps &props) : Window(props)
    {
        Init(props);
    }

    WindowSFML::~WindowSFML()
    {
        Shutdown();
    }

    void WindowSFML::OnUpdate()
    {
        sf::Event event;

        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                m_window.close();
        }
    }

    unsigned int WindowSFML::GetWidth() const
    {
        return m_window.getSize().x;
    }

    unsigned int WindowSFML::GetHeight() const
    {
        return m_window.getSize().y;
    }

    sf::RenderWindow &WindowSFML::GetWindow()
    {
        return m_window;
    }

    void WindowSFML::SetEventCallback(const EventCallbackFn &callback)
    {
        m_eventCallback = callback;
    }

    void WindowSFML::SetVSync(bool enabled)
    {
        m_window.setVerticalSyncEnabled(enabled);
    }

    bool WindowSFML::IsVSync() const
    {
        return m_window.hasFocus();
    }

    void WindowSFML::setFpsLimit(unsigned int fps)
    {
        m_window.setFramerateLimit(fps);
    }

    void WindowSFML::Init(const WindowProps &props)
    {
        m_window.create(sf::VideoMode(props.Width, props.Height), props.Title);
    }

    void WindowSFML::Shutdown()
    {
        m_window.close();
    };
} // namespace RType::Graphics
