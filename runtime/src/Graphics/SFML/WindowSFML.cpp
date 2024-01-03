/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** WindowSFML
*/

#include "WindowSFML.hpp"

Window *RType::Graphics::WindowSFML::Create(const WindowProps &props)
{
    return new WindowSFML(props);
}

RType::Graphics::WindowSFML::Window(const WindowProps &props)
{
    Init(props);
}

RType::Graphics::WindowSFML::~Window()
{
    Shutdown();
}

void RType::Graphics::WindowSFML::OnUpdate()
{
    sf::Event event;

    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_window.close();
    }
}

unsigned int RType::Graphics::WindowSFML::GetWidth() const
{
    return m_window.getSize().x;
}

unsigned int RType::Graphics::WindowSFML::GetHeight() const
{
    return m_window.getSize().y;
}

sf::RenderWindow &RType::Graphics::WindowSFML::GetWindow()
{
    return m_window;
}

void RType::Graphics::WindowSFML::SetEventCallback(const EventCallbackFn &callback)
{
    m_eventCallback = callback;
}

void RType::Graphics::WindowSFML::SetVSync(bool enabled)
{
    m_window.setVerticalSyncEnabled(enabled);
}

bool RType::Graphics::WindowSFML::IsVSync() const
{
    return m_window.hasFocus();
}

void RType::Graphics::WindowSFML::Init(const WindowProps &props)
{
    m_window.create(sf::VideoMode(props.Width, props.Height), props.Title);
}

void RType::Graphics::WindowSFML::Shutdown()
{
    m_window.close();
};
