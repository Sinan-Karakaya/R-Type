/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ILayer
*/

#pragma once

namespace RType::Editor
{
    class ILayer
    {
    public:
        virtual ~ILayer() = default;

        /**
         * @brief This function is called when the layer is attached to the application.
         * 
         * @details It is a pure virtual function that needs to be implemented by the derived classes.
         *          This function is typically used for initializing the layer and its resources.
         */
        virtual void OnAttach() = 0;
        /**
         * @brief Detaches the layer from the application.
         * 
         * This function is called when the layer is being detached from the application.
         * It should be implemented by derived classes to perform any necessary cleanup or
         * finalization tasks.
         */
        virtual void OnDetach() = 0;
        /**
         * @brief This function is called to update the layer.
         * 
         * @details This function should be implemented by derived classes to perform any necessary updates for the layer.
         * It is called once per frame.
         */
        virtual void OnUpdate() = 0;
        /**
         * @brief Renders the layer.
         * 
         * This pure virtual function is responsible for rendering the layer.
         * Subclasses must implement this function to define how the layer is rendered.
         */
        virtual void OnRender() = 0;
    };
} // namespace RType::Editor
