#pragma once

#include <algorithm>
#include <filesystem>

#include "Editor.hpp"
#include "Layers/ILayer.hpp"

// TODO: Must add handle for drag event
namespace RType::Editor
{
class AssetExplorer : public ILayer
{
  public:
    AssetExplorer()
    {
        OnAttach();
    };
    ~AssetExplorer()
    {
        OnDetach();
    };

    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate() override;
    void OnRender() override;

  private:
    void f_displayDirectory(const std::filesystem::path &path);
    void f_displayFile(const std::filesystem::path &path);

  private:
    std::filesystem::path m_currentPath;
    std::vector<std::filesystem::path> m_assets;

    sf::Texture m_folderTexture;
    sf::Texture m_fileTexture;
};
} // namespace RType::Editor
