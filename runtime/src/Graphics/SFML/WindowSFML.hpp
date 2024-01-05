/*
** EPITECH PROJECT, 2023
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Window
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <SFML/Graphics.hpp>

#include "Graphics/Window.hpp"

namespace RType::Graphics
{
    class WindowSFML : public Window
    {
    public:
        /**
         * @brief Create a Window object
         *
         * @param props
         * @return Window*
         * @note This function is used to create a window
         */
        static WindowSFML *Create(const WindowProps &props = WindowProps());

        WindowSFML(const WindowProps &props);
        ~WindowSFML();

        void OnUpdate() override;
        unsigned int GetWidth() const override;
        unsigned int GetHeight() const override;

        // Added
        sf::RenderWindow &GetWindow();

        // Window attributes
        void SetEventCallback(const EventCallbackFn &callback) override;
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        void setFpsLimit(unsigned int fps) override;

    protected:
    private:
        void Init(const WindowProps &props);
        void Shutdown();

    private:
        sf::RenderWindow m_window;
        EventCallbackFn m_eventCallback;
    };
} // namespace RType::Graphics

#endif /* !WINDOW_HPP_ */
