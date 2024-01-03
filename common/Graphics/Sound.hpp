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
    class Sound {
        public:

            enum Status {
                Stopped,
                Paused,
                Playing
            };

            Sound();
            Sound(const SoundBuffer &buffer);
            ~Sound();

            virtual void setBuffer(const SoundBuffer &buffer);
            virtual void setLoop(bool loop);
            virtual void setVolume(float volume);

            virtual const SoundBuffer &getBuffer() const;
            virtual bool getLoop() const;
            virtual float getVolume() const;
            virtual Status getStatus() const;

            virtual void play();
            virtual void pause();
            virtual void stop();

            virtual void resetBuffer();
    };
} // namespace RType::Graphics
