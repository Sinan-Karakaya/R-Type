/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** SoundBufferSFML
*/

#include "SoundBufferSFML.hpp"

namespace RType::Graphics
{
    SoundBufferSFML::SoundBufferSFML()
    {
        buffer = sf::SoundBuffer();
    }

    SoundBufferSFML::~SoundBufferSFML()
    {
    }

    bool SoundBufferSFML::loadFromFile(const std::string &filename)
    {
        return buffer.loadFromFile(filename);
    }

    uint32_t SoundBufferSFML::getDuration() const
    {
        return buffer.getDuration().asMilliseconds();
    }

} // namespace RType::Graphics
