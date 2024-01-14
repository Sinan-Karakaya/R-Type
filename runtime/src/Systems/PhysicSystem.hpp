/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PhysicSystem
*/

#ifndef PHYSICSYSTEM_HPP_
#define PHYSICSYSTEM_HPP_

#include "RType.hpp"

namespace RType::Runtime
{
    class PhysicSystem : public ECS::ISystem
    {
    public:
        PhysicSystem() = default;
        ~PhysicSystem() = default;

        void run(RType::Runtime::ECS::Registry &registry, float dt) override;

        std::string GetName() const override { return "PhysicSystem"; }
    };
} // namespace RType::Runtime

#endif /* !PHYSICSYSTEM_HPP_ */
