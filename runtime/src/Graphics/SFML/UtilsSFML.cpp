/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** UtilsSFML
*/

#include "UtilsSFML.hpp"

namespace RType::Graphics
{
    TimeSFML::TimeSFML()
    {
        m_time = sf::Time::Zero;
    }

    float TimeSFML::asSeconds() const
    {
        return m_time.asSeconds();
    }

    int32_t TimeSFML::asMilliseconds() const
    {
        return m_time.asMilliseconds();
    }

    int64_t TimeSFML::asMicroseconds() const
    {
        return m_time.asMicroseconds();
    }

    void TimeSFML::setTime(sf::Time time)
    {
        m_time = time;
    }

    ClockSFML::ClockSFML()
    {
        m_clock = sf::Clock();
    }

    ClockSFML::~ClockSFML() {}

    Time ClockSFML::getElapsedTime() const
    {
        /*
        TimeSFML time;

        time.setTime(m_clock.getElapsedTime());

        return time;
        */
    }

    Time ClockSFML::restart()
    {
        /*
        TimeSFML time;

        time.m_time = m_clock.restart();
        return time;
        */
    }
} // namespace RType::Graphics
