/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** SoundBufferSFML
*/

#pragma once

#include "Graphics/SoundBuffer.hpp"
#include <SFML/Audio/SoundBuffer.hpp>

namespace RType::Graphics
{
    class SoundBufferSFML : public SoundBuffer{
        public:
            SoundBufferSFML();
            ~SoundBufferSFML();

            bool loadFromFile(const std::string &filename) override;
            uint32_t getDuration() const override;

        public:
            sf::SoundBuffer buffer;
    };
} // namespace RType::Graphics
