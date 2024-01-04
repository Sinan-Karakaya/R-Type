/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** ShowUtils
*/

#pragma once

#include <unordered_map>
#include "Editor.hpp"

namespace RType::Editor {
    class ShowUtils {
    public:
        static void ShowAll(RType::Runtime::IRuntime &runtime);

        static void ShowCollisionBoxes(RType::Runtime::IRuntime &runtime);
    private:
        static std::unordered_map<RType::Runtime::ECS::Entity, sf::RectangleShape> m_collisionBoxes;
    };
}