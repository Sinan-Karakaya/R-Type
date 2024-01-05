/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Utils
*/

#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

#include "Graphics/Utils.hpp"

namespace RType::Graphics
{
    class TimeSFML : Time
    {
        public:
            TimeSFML();

            float asSeconds() const override;
            int32_t asMilliseconds() const override;
            int64_t asMicroseconds() const override;

            void setTime(sf::Time time);

        private:
            sf::Time m_time;
    };

    class ClockSFML : Clock
    {
        public:
            ClockSFML();
            ~ClockSFML();

            Time getElapsedTime() const override;
            Time restart() override;

        private:
            sf::Clock m_clock;
    };

} // namespace RType::Graphics