/*
** EPITECH PROJECT, 2023
** Project
** File description:
** Entity
*/

#pragma once

#include <cstdlib>

namespace RType::Runtime::ECS
{

    class Entity
    {
    public:
        explicit Entity(std::size_t id) : m_id(id) {}
        explicit operator std::size_t() const { return m_id; }

    private:
        std::size_t m_id;
    };

} // namespace RType::Runtime::ECS
