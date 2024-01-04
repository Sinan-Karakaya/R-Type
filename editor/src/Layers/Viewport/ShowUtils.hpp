/*
** EPITECH PROJECT, 2024
** R-Type [WSL: Ubuntu-22.04]
** File description:
** ShowUtils
*/

#ifndef SHOWUTILS_HPP_
#define SHOWUTILS_HPP_

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

#endif /* !SHOWUTILS_HPP_ */
