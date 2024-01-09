/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** MoveableSystem
*/

#ifndef MOVEABLESYSTEM_HPP_
#define MOVEABLESYSTEM_HPP_

#include "RType.hpp"

namespace RType::Runtime
{
    class MoveableSystem : public ECS::ISystem
    {
    public:
        MoveableSystem() = default;
        ~MoveableSystem() = default;

        void run(RType::Runtime::ECS::Registry &registry) override;

    private:
        void updateSprite(RType::Runtime::ECS::Registry &registry, RType::Runtime::ECS::Entity entity);
        void updateCircleShape(RType::Runtime::ECS::Registry &registry, RType::Runtime::ECS::Entity entity);
    };
} // namespace RType::Runtime

#endif /* !MOVEABLESYSTEM_HPP_ */
