#include "AssetExplorer.hpp"

namespace RType::Editor
{
void AssetExplorer::OnAttach()
{
    m_currentPath = std::filesystem::path(g_projectInfos.path);

    // store all assets from the project
    for (auto &p : std::filesystem::recursive_directory_iterator(m_currentPath)) {
        m_assets.push_back(p.path());
    }

    // load textures
    try {
        m_folderTexture.loadFromFile("./assets/icons/folder.png");
        m_fileTexture.loadFromFile("./assets/icons/files.png");
    } catch (const std::exception &e) {
        EDITOR_LOG_CRITICAL("Failed to load textures: %s", e.what());
        exit(84);
    }
}

void AssetExplorer::OnDetach() {}

void AssetExplorer::OnUpdate() {}

void AssetExplorer::OnRender()
{
    ImGui::Begin("Asset Explorer");
    const std::size_t iconSize = 128 + 16; // 16 is the padding
    const float windowWidth = ImGui::GetContentRegionAvail().x;

    std::size_t numCols = (std::size_t)(windowWidth / iconSize);
    numCols = numCols == 0 ? 1 : numCols;
    ImGui::Columns(numCols, nullptr, false);

    for (std::size_t idx = 0; auto &asset : m_assets) {
        if (std::filesystem::is_directory(asset)) {
            f_displayDirectory(asset);
        } else {
            f_displayFile(asset);
        }

        ImGui::NextColumn();
        ++idx;
    }

    ImGui::Columns(1);
    ImGui::End();
}

void AssetExplorer::f_displayDirectory(const std::filesystem::path &path)
{
    ImGui::ImageButton(m_folderTexture, {128, 128});
    ImGui::Text("%s", path.filename().string().c_str());
}

void AssetExplorer::f_displayFile(const std::filesystem::path &path)
{
    ImGui::ImageButton(m_fileTexture, {128, 128});
    ImGui::Text("%s", path.filename().string().c_str());
}
} // namespace RType::Editor
