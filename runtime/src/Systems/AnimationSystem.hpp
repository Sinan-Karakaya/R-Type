/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** AnimationSystem
*/

#ifndef ANIMATIONSYSTEM_HPP_
#define ANIMATIONSYSTEM_HPP_

#include "RType.hpp"

namespace RType::Runtime
{
    class AnimationSystem : public ECS::ISystem
    {
    public:
        AnimationSystem() = default;
        ~AnimationSystem() = default;

        void run(RType::Runtime::ECS::Registry &registry, float dt) override;
    };
} // namespace RType::Runtime

#endif /* !ANIMATIONSYSTEM_HPP_ */
