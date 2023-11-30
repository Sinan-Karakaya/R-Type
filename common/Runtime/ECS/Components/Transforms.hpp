#pragma once

#include <cstddef>

#include <SFML/Graphics.hpp>

namespace RType::ECS::Components
{

    struct Velocity {
        std::size_t x = 0;
        std::size_t y = 0;
    };

    struct Transformable : public sf::Transformable {
    };

} // namespace RType::ECS::Components
