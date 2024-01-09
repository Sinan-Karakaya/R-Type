/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** ShowUtils
*/

#include "ShowUtils.hpp"

namespace RType::Editor
{
    std::unordered_map<RType::Runtime::ECS::Entity, sf::RectangleShape> ShowUtils::m_collisionBoxes;
    std::unordered_map<RType::Runtime::ECS::Entity, bool> ShowUtils::showCollisionBoxes;

    void ShowUtils::ShowAll(RType::Runtime::IRuntime &runtime)
    {
        ShowCollisionBoxes(runtime);
    }

    void ShowUtils::ShowCollisionBoxes(RType::Runtime::IRuntime &runtime)
    {
        for (auto &entity : runtime.GetEntities()) {
            if (showCollisionBoxes.find(entity) == showCollisionBoxes.end())
                showCollisionBoxes[entity] = false;
            if (!showCollisionBoxes[entity])
                continue;
            SKIP_EXCEPTIONS({
                auto &controllable =
                    runtime.GetRegistry().GetComponent<RType::Runtime::ECS::Components::Controllable>(entity);
                if (!controllable.isActive)
                    continue;
            })

            SKIP_EXCEPTIONS({
                auto &iaControllable =
                    runtime.GetRegistry().GetComponent<RType::Runtime::ECS::Components::IAControllable>(entity);
                if (!iaControllable.isActive)
                    continue;
            })

            SKIP_EXCEPTIONS({
                auto &collisionBox =
                    runtime.GetRegistry().GetComponent<RType::Runtime::ECS::Components::CollisionBox>(entity);
                auto &transform =
                    runtime.GetRegistry().GetComponent<RType::Runtime::ECS::Components::Transform>(entity);

                if (ShowUtils::m_collisionBoxes.find(entity) == ShowUtils::m_collisionBoxes.end()) {
                    ShowUtils::m_collisionBoxes[entity] = sf::RectangleShape();
                    ShowUtils::m_collisionBoxes[entity].setFillColor(sf::Color(255, 0, 0, 100));
                    ShowUtils::m_collisionBoxes[entity].setOutlineColor(sf::Color(255, 0, 0, 200));
                    ShowUtils::m_collisionBoxes[entity].setOutlineThickness(2);
                }
                ShowUtils::m_collisionBoxes[entity].setPosition(transform.position.x, transform.position.y);
                ShowUtils::m_collisionBoxes[entity].setSize(sf::Vector2f(collisionBox.width, collisionBox.height));
                ShowUtils::m_collisionBoxes[entity].setOrigin(collisionBox.width / 2, collisionBox.height / 2);
                runtime.GetRenderTexture().draw(ShowUtils::m_collisionBoxes[entity]);
            })
        }
    }
} // namespace RType::Editor
