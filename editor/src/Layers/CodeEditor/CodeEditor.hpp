/*
** EPITECH PROJECT, 2023
** CodeEditor
** File description:
** Created by Mathis Le Bonniec on 09/01/2024
*/

#pragma once

#include <fstream>

#include "Editor.hpp"
#include "Layers/ILayer.hpp"
#include "TextEditor.h"

namespace RType::Editor {
    class CodeEditor : public ILayer
    {
    public:
        CodeEditor(std::optional<std::filesystem::path> &filePath);
        ~CodeEditor();

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnRender() override;

    private:
        /**
         * @brief Updates the editor with the content of the current file.
         */
        void UpdateEditorWithFileContent();

        /**
         * @brief Saves the current file.
         */
        void SaveFile();

        /**
         * @brief Closes the current file without saving it.
         * The m_filePath is set to std::nullopt.
         */
        void CloseWithoutSaving();

    private:
        std::optional<std::filesystem::path> m_lastFilePath;
        std::optional<std::filesystem::path> &m_filePath;
        std::string m_title;
        TextEditor m_editor;

    };
}
