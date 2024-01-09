/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** AnimationSystem
*/

#include "AnimationSystem.hpp"

namespace RType::Runtime {
    
    void AnimationSystem::run(RType::Runtime::ECS::Registry &registry)
    {
        for (const auto &entity : entities) {
            auto &drawable = registry.GetComponent<RType::Runtime::ECS::Components::Drawable>(entity);
            if (drawable.isAnimated && drawable.autoPlay) {
                float timeElapsed = drawable.clock.getElapsedTime().asSeconds();
                if (timeElapsed < drawable.frameDuration) {
                    return;
                }
                if (drawable.currentFrame >= drawable.frameCount) {
                    drawable.currentFrame = 0;
                    drawable.rect.left = drawable.startPosition;
                } else {
                    ++drawable.currentFrame;
                    drawable.rect.left += drawable.leftDecal;
                }
                drawable.sprite.setTextureRect((sf::IntRect)drawable.rect);
                drawable.clock.restart();
            }
        }
    }
}
