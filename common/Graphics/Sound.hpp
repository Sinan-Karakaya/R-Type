/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Sound
*/

#pragma once

#include "SoundBuffer.hpp"

namespace RType::Graphics
{
    class Sound
    {
    public:
        enum Status {
            Stopped,
            Paused,
            Playing
        };

        Sound();
        Sound(const SoundBuffer &buffer);
        ~Sound();

        virtual void setBuffer(const SoundBuffer &buffer) = 0;
        virtual void setLoop(bool loop) = 0;
        virtual void setVolume(float volume) = 0;

        virtual const SoundBuffer &getBuffer() const = 0;
        virtual bool getLoop() const = 0;
        virtual float getVolume() const = 0;
        virtual Status getStatus() const = 0;

        virtual void play() = 0;
        virtual void pause() = 0;
        virtual void stop() = 0;

        virtual void resetBuffer();
    };
} // namespace RType::Graphics
