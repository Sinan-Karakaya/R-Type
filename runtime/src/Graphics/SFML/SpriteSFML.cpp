/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** SpriteSFML
*/

#include "SpriteSFML.hpp"

namespace RType::Graphics
{
    SpriteSFML::SpriteSFML()
    {
        this->sprite = sf::Sprite();
    }

    SpriteSFML::SpriteSFML(const TextureSFML &texture)
    {
        this->sprite = sf::Sprite(texture.texture);
    }

    SpriteSFML::SpriteSFML(const TextureSFML &texture, const IntRect &rectangle)
    {
        this->sprite =
            sf::Sprite(texture.texture, sf::IntRect(rectangle.left, rectangle.top, rectangle.width, rectangle.height));
    }

    void SpriteSFML::setTexture(const Texture &texture, bool resetRect)
    {
        sprite.setTexture(*(sf::Texture *)texture.getTexture(), resetRect);
    }

    void SpriteSFML::setTextureRect(const IntRect &rectangle)
    {
        sprite.setTextureRect(sf::IntRect(rectangle.left, rectangle.top, rectangle.width, rectangle.height));
    }

    void SpriteSFML::setColor(const Color &color)
    {
        sprite.setColor(sf::Color(color.GetA(), color.GetG(), color.GetB(), color.GetA()));
    }

    const Texture *SpriteSFML::getTexture() const
    {
        const sf::Texture* sfmlTexture = sprite.getTexture();

        return new TextureSFML(*sfmlTexture);
    }

    const IntRect &SpriteSFML::getTextureRect() const
    {
        return *(IntRect *)&sprite.getTextureRect();
    }

    const Color SpriteSFML::getColor() const
    {
        const sf::Color& sfmlColor = sprite.getColor();

        return ColorSFML(sfmlColor);
    }

    const FloatRect SpriteSFML::getLocalBounds() const
    {
        sf::FloatRect sfmlFloatRect = sprite.getLocalBounds();

        return FloatRect(sfmlFloatRect.left, sfmlFloatRect.top, sfmlFloatRect.width, sfmlFloatRect.height);
    }

    const FloatRect SpriteSFML::getGlobalBounds() const
    {
        sf::FloatRect sfmlFloatRect = sprite.getGlobalBounds();

        return FloatRect(sfmlFloatRect.left, sfmlFloatRect.top, sfmlFloatRect.width, sfmlFloatRect.height);
    }
} // namespace RType::Graphics
