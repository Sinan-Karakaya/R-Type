/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** TextureSFML
*/

#include "TextureSFML.hpp"

namespace RType::Graphics
{
    TextureSFML::TextureSFML()
    {
        texture = sf::Texture();
    }

    TextureSFML::TextureSFML(const Texture &texture)
    {
        this->texture = *(sf::Texture *)texture.getTexture();
    }

    TextureSFML::~TextureSFML() {}

    bool TextureSFML::create(uint32_t width, uint32_t height)
    {
        return texture.create(width, height);
    }

    bool TextureSFML::loadFromFile(const std::string &filename, const IntRect &area)
    {
        sf::IntRect rect(area.left, area.top, area.width, area.height);
        return texture.loadFromFile(filename, rect);
    }

    Vector2u TextureSFML::getSize() const
    {
        sf::Vector2u vect = texture.getSize();
        return Vector2u(vect.x, vect.y);
    }

    // void TextureSFML::update(const Texture &texture)
    // {
    //     this->texture.update(texture);
    // }

    void TextureSFML::setSmooth(bool smooth)
    {
        texture.setSmooth(smooth);
    }

    bool TextureSFML::isSmooth() const
    {
        return texture.isSmooth();
    }

    void TextureSFML::setRepeated(bool repeated)
    {
        texture.setRepeated(repeated);
    }

    bool TextureSFML::isRepeated() const
    {
        return texture.isRepeated();
    }

    void *TextureSFML::getTexture() const
    {
        return (void *)&texture;
    }

} // namespace RType::Graphics
