/*
** EPITECH PROJECT, 2023
** CodeEditor
** File description:
** Created by Mathis Le Bonniec on 09/01/2024
*/

#include "CodeEditor.hpp"

namespace RType::Editor
{
    CodeEditor::CodeEditor(std::optional<std::filesystem::path> &filePath):
          m_lastFilePath(std::nullopt),
          m_filePath(filePath),
          m_title("Lua Editor")
    {
        OnAttach();
    }

    CodeEditor::~CodeEditor()
    {
        OnDetach();
    }

    void CodeEditor::OnAttach() {
        this->m_editor.SetLanguageDefinition(TextEditor::LanguageDefinition::Lua());
        this->m_editor.SetReadOnly(false);
        this->m_editor.SetPalette(TextEditor::GetDarkPalette());
    }

    void CodeEditor::OnDetach() {}

    void CodeEditor::OnUpdate() {
        this->UpdateEditorWithFileContent();
    }

    void CodeEditor::OnRender() {
        if (!this->m_filePath.has_value())
            return;

        ImGui::Begin(this->m_title.c_str());

        if (ImGui::Button(ICON_FA_WINDOW_CLOSE_O))
            ImGui::OpenPopup("Quit");

        ImGui::SameLine();
        if (ImGui::Button(ICON_FA_FLOPPY_O))
            this->SaveFile(this->m_filePath);

        ImGui::SameLine();
        ImGui::Text("%s", this->m_filePath.value().filename().c_str());

        if (ImGui::BeginPopupModal("Quit", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text("You're about to quit the editor without saving your file.");

            if (ImGui::Button("Cancel"))
                ImGui::CloseCurrentPopup();

            ImGui::SameLine();
            if (ImGui::Button("Quit"))
                this->CloseWithoutSaving();

            ImGui::EndPopup();
        }

        ImGui::Separator();

        this->m_editor.Render(this->m_title.c_str());

        ImGui::End();
    }

    void CodeEditor::UpdateEditorWithFileContent()
    {
        if (!this->m_filePath.has_value() || this->m_lastFilePath == this->m_filePath)
            return;

        this->SaveFile(this->m_lastFilePath);
        this->m_lastFilePath = this->m_filePath;
        std::ifstream file(this->m_filePath.value());
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        this->m_editor.SetText(content);
    }

    void CodeEditor::SaveFile(std::optional<std::filesystem::path> filePath) {
        if (!filePath.has_value())
            return;

        std::ofstream file(filePath.value());
        file << this->m_editor.GetText();
        file.close();
    }

    void CodeEditor::CloseWithoutSaving() {
        this->m_filePath = std::nullopt;
        ImGui::CloseCurrentPopup();
    }
}
