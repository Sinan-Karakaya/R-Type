/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** SoundSFML
*/

#pragma once

#include "Graphics/Sound.hpp"
#include <SFML/Audio/Sound.hpp>

namespace RType::Graphics
{
    class SoundSFML : public Sound
    {
    public:
        SoundSFML();
        ~SoundSFML();

        void setBuffer(const SoundBuffer &buffer) override;
        void setLoop(bool loop) override;
        void setVolume(float volume) override;

        // const SoundBuffer &getBuffer() const override;
        bool getLoop() const override;
        float getVolume() const override;
        Status getStatus() const override;

        void play() override;
        void pause() override;
        void stop() override;

        void resetBuffer() override;

    public:
        sf::Sound sound;
    };
} // namespace RType::Graphics
