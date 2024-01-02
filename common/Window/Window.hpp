/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Window
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "IWindow.hpp"

namespace RType::Window
{
    class Window : public IWindow
    {
    public:
        /**
         * @brief Create a Window object
         *
         * @param props
         * @return Window*
         * @note This function is used to create a window
         */
        static Window *Create(const WindowProps &props = WindowProps()) { return new Window(props); };
        Window(const WindowProps &props) { Init(props); };
        ~Window() { Shutdown(); };

        void OnUpdate() override
        {
            sf::Event event;

            while (m_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    m_window.close();
            }
        };

        unsigned int GetWidth() const override { return m_window.getSize().x; };

        unsigned int GetHeight() const override { return m_window.getSize().y; };

        // Added
        sf::RenderWindow &GetWindow() override { return m_window; };

        // Window attributes
        void SetEventCallback(const EventCallbackFn &callback) override { m_eventCallback = callback; };
        void SetVSync(bool enabled) override { m_window.setVerticalSyncEnabled(enabled); };
        bool IsVSync() const override { return m_window.hasFocus(); };

    protected:
    private:
        void Init(const WindowProps &props) { m_window.create(sf::VideoMode(props.Width, props.Height), props.Title); };
        void Shutdown() { m_window.close(); };

    private:
        sf::RenderWindow m_window;
        EventCallbackFn m_eventCallback;
    };
} // namespace RType::Window

#endif /* !WINDOW_HPP_ */
