/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** SoundSFML
*/

#include "SoundSFML.hpp"

namespace RType::Graphics
{
    SoundSFML::SoundSFML()
    {
        sound = sf::Sound();
    }

    SoundSFML::~SoundSFML() {}

    void SoundSFML::setBuffer(const SoundBuffer &buffer)
    {
        sound.setBuffer((const sf::SoundBuffer &)buffer);
    }

    void SoundSFML::setLoop(bool loop)
    {
        sound.setLoop(loop);
    }

    void SoundSFML::setVolume(float volume)
    {
        sound.setVolume(volume);
    }

    /* const SoundBuffer &SoundSFML::getBuffer() const
    {
        return SoundBuffer();
    } */

    bool SoundSFML::getLoop() const
    {
        return sound.getLoop();
    }

    float SoundSFML::getVolume() const
    {
        return sound.getVolume();
    }

    SoundSFML::Status SoundSFML::getStatus() const
    {
        return static_cast<SoundSFML::Status>(sound.getStatus());
    }

    void SoundSFML::play()
    {
        sound.play();
    }

    void SoundSFML::pause()
    {
        sound.pause();
    }

    void SoundSFML::stop()
    {
        sound.stop();
    }

    void SoundSFML::resetBuffer()
    {
        sound.resetBuffer();
    }

} // namespace RType::Graphics
