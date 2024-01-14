/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** PhysicSystem
*/

#include "PhysicSystem.hpp"

namespace RType::Runtime
{
    void PhysicSystem::run(RType::Runtime::ECS::Registry &registry, float dt)
    {
        for (auto &entity : entities) {
            auto &transform = registry.GetComponent<RType::Runtime::ECS::Components::Transform>(entity);
            auto &rigidbody = registry.GetComponent<RType::Runtime::ECS::Components::RigidBody>(entity);

            if (rigidbody.isKinematic)
                continue;

            if (rigidbody.isColliding) {
                rigidbody.velocity = sf::Vector2f(0, 0);
                rigidbody.acceleration = sf::Vector2f(0, 0);
                rigidbody.isColliding = false;
                return;
            }

            if (rigidbody.useGravity) {
                sf::Vector2f gravitationalForce = sf::Vector2f(0, 9.81f) * rigidbody.mass;
                rigidbody.acceleration += gravitationalForce;

                transform.position += rigidbody.velocity * dt + 0.5f * rigidbody.acceleration * dt * dt;
                rigidbody.velocity += rigidbody.acceleration * dt;

                rigidbody.acceleration = sf::Vector2f(0, 0);
            }
        }
    }
} // namespace RType::Runtime
