/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** MoveableSystem
*/

#include "MoveableSystem.hpp"

namespace RType::Runtime
{

    void MoveableSystem::run(RType::Runtime::ECS::Registry &registry, float dt)
    {
        (void)dt;
        for (const auto &entity : entities) {
            updateSprite(registry, entity);
            updateCircleShape(registry, entity);
        }
    }

    void MoveableSystem::updateSprite(RType::Runtime::ECS::Registry &registry, RType::Runtime::ECS::Entity entity)
    {
        SKIP_EXCEPTIONS({
            const auto &transform = registry.GetComponent<RType::Runtime::ECS::Components::Transform>(entity);
            auto &drawable = registry.GetComponent<RType::Runtime::ECS::Components::Drawable>(entity);
            drawable.sprite.setPosition(transform.position);
            drawable.sprite.setRotation(transform.rotation.x);
            drawable.sprite.setScale(transform.scale);
            drawable.sprite.setOrigin(drawable.sprite.getLocalBounds().width / 2,
                                      drawable.sprite.getLocalBounds().height / 2);
        })
    }

    void MoveableSystem::updateCircleShape(RType::Runtime::ECS::Registry &registry, RType::Runtime::ECS::Entity entity)
    {
        SKIP_EXCEPTIONS({
            const auto &transform = registry.GetComponent<RType::Runtime::ECS::Components::Transform>(entity);
            auto &circle = registry.GetComponent<RType::Runtime::ECS::Components::CircleShape>(entity);
            circle.circle.setOrigin(circle.circle.getLocalBounds().width / 2,
                                    circle.circle.getLocalBounds().height / 2);
            circle.circle.setPosition(transform.position);
            circle.circle.setRotation(transform.rotation.x);
            circle.circle.setScale(transform.scale);
        })
    }

} // namespace RType::Runtime
