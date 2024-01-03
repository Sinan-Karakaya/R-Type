/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** Font
*/

#pragma once

namespace RType::Graphics
{
    class Font
    {
    public:
        Font();
        Font(const Font &font);
        ~Font();

        virtual bool loadFromFile(const std::string &filename) = 0;
        virtual void setSmooth(bool smooth) = 0;
        virtual bool isSmooth() const = 0;
    };
} // namespace RType::Graphics
