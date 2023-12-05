/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Inspector
*/

#pragma once

#include "Editor.hpp"
#include "Layers/ILayer.hpp"

namespace RType::Editor
{
    class Inspector : public ILayer
    {
    public:
        Inspector() { OnAttach(); }
        ~Inspector() override { OnDetach(); }

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnRender() override;
    };
} // namespace RType::Editor
