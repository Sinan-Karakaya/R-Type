#pragma once

#include <cstddef>

namespace RType::ECS::Components
{

    struct Position {
        std::size_t x = 0;
        std::size_t y = 0;
    };

    struct Velocity {
        std::size_t x = 0;
        std::size_t y = 0;
    };

} // namespace RType::ECS::Components
