/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Random
*/

#pragma once

#include <random>

namespace RType::Utils {

class Random {
public:
    static float GetFloat(float min = 0.f, float max = 1.f) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(min, max);
        return dis(gen);
    }
};

}