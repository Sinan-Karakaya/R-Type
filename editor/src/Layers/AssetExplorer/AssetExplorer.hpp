/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** AssetExplorer
*/

#pragma once

#include <algorithm>
#include <filesystem>
#include <fstream>

#include "Editor.hpp"
#include "Layers/ILayer.hpp"

// TODO: Must add handle for drag event
// Should probably use a Serializer, descending from ISerializer
namespace RType::Editor
{
    class AssetExplorer : public ILayer
    {
    public:
        AssetExplorer() { OnAttach(); };
        ~AssetExplorer() { OnDetach(); };

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnRender() override;

    private:
        /**
         * @brief Displays the toolbar for the asset explorer.
         */
        void f_displayToolBar();
        /**
         * Retrieves the current workspace and filter paths.
         *
         * @return A vector of filesystem paths representing the current workspace and filter.
         */
        const std::vector<std::filesystem::path> f_getCurrentWorkspaceAndFilter();
        /**
         * @brief Refreshes the assets in the asset explorer.
         */
        void f_refreshAssets();
        /**
         * @brief Open the specified file with the default application associated with its file type.
         *
         * @param path The path to the file to be opened.
         */
        void f_openWithDefaultApp(const std::filesystem::path &path);

    private:
        std::filesystem::path m_root;
        std::filesystem::path m_currentPath;
        std::vector<std::pair<std::filesystem::path, bool>> m_assets;

        sf::Texture m_folderTexture;
        sf::Texture m_fileTexture;

        char m_search[64] = {0};
    };
} // namespace RType::Editor
