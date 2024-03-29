/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** AssetExplorer
*/

#include "AssetExplorer.hpp"

namespace RType::Editor
{
    void AssetExplorer::OnAttach()
    {
        m_root = std::filesystem::path(g_projectInfos.path);
        m_currentPath = std::filesystem::path(g_projectInfos.path);

        f_refreshAssets();

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
        f_displayToolBar();
        const std::size_t iconSize = 128 + 16; // 16 is the padding
        const float windowWidth = ImGui::GetContentRegionAvail().x;

        std::size_t numCols = (std::size_t)(windowWidth / iconSize);
        numCols = numCols == 0 ? 1 : numCols;
        ImGui::Columns(numCols, nullptr, false);

        const auto assets = f_getCurrentWorkspaceAndFilter();

        for (std::size_t idx = 0; auto &asset : assets) {
            const bool isDirectory = std::filesystem::is_directory(asset);

            ImGui::PushID(idx);
            if (ImGui::ImageButton(asset.string().c_str(), isDirectory ? m_folderTexture : m_fileTexture, {128, 128})) {
                if (isDirectory) {
                    m_currentPath = asset;
                } else {
                    f_openWithDefaultApp(asset);
                }
            }
            if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
                ImGui::SetDragDropPayload("PREFAB_ADD_ENTITY", asset.filename().stem().string().c_str(),
                                          asset.string().size());
                ImGui::Text("%s", asset.filename().stem().string().c_str());
                ImGui::EndDragDropSource();
            }
            ImGui::PopID();

            auto it =
                std::find_if(m_assets.begin(), m_assets.end(), [&asset](const auto &p) { return p.first == asset; });
            if (it != m_assets.end()) {
                std::size_t index = std::distance(m_assets.begin(), it);
                ImGui::Checkbox(("##" + asset.string()).c_str(), &m_assets[index].second);
            }
            ImGui::SameLine();
            ImGui::Text("%s", asset.filename().string().c_str());

            ImGui::NextColumn();
            ++idx;
        }

        ImGui::Columns(1);
        ImGui::End();
    }

    void AssetExplorer::f_displayToolBar()
    {
        bool isRoot = m_currentPath == m_root;
        if (isRoot)
            ImGui::BeginDisabled();
        if (ImGui::Button(ICON_FA_ARROW_LEFT))
            m_currentPath = m_currentPath.parent_path();
        if (isRoot)
            ImGui::EndDisabled();

        // ------------------- Create -------------------
        ImGui::SameLine();
        if (ImGui::Button(ICON_FA_FOLDER)) {
            ImGui::OpenPopup("Create a folder?");
        }
        ImGui::SameLine();
        if (ImGui::Button(ICON_FA_FILE)) {
            ImGui::OpenPopup("Create a file?");
        }
        ImGui::SameLine();
        if (ImGui::Button(ICON_FA_REFRESH)) {
            f_refreshAssets();
        }

        if (ImGui::BeginPopupModal("Create a folder?", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
            static char folderName[64] = {0};
            ImGui::InputText("Folder name", folderName, IM_ARRAYSIZE(folderName));
            if (ImGui::Button("Create")) {
                std::filesystem::create_directory(m_currentPath / folderName);
                f_refreshAssets();
                ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel")) {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }

        if (ImGui::BeginPopupModal("Create a file?", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
            static char fileName[64] = {0};
            ImGui::InputText("File name", fileName, IM_ARRAYSIZE(fileName));
            if (ImGui::Button("Create")) {
                f_createFile(m_currentPath / fileName);
                f_refreshAssets();
                ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel")) {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }

        // ------------------- Delete -------------------
        ImGui::SameLine();
        if (ImGui::Button(ICON_FA_TRASH)) {
            for (std::size_t idx = 0; auto &asset : m_assets) {
                if (asset.second) {
                    std::filesystem::remove(asset.first);
                }
                ++idx;
            }
            f_refreshAssets();
        }

        // ------------------- Search -------------------
        ImGui::SameLine();
        ImGui::InputText(ICON_FA_SEARCH, m_search, IM_ARRAYSIZE(m_search));
        ImGui::Separator();
    }

    const std::vector<std::filesystem::path> AssetExplorer::f_getCurrentWorkspaceAndFilter()
    {
        std::vector<std::filesystem::path> filteredAssets;

        for (const auto &entry : std::filesystem::directory_iterator(m_currentPath)) {
            std::string filename = entry.path().filename().string();
            if (filename.find('.') == 0 || filename.find(m_search) == std::string::npos)
                continue;
            filteredAssets.push_back(entry.path());
        }
        return filteredAssets;
    }

    void AssetExplorer::f_refreshAssets()
    {
        m_assets.clear();
        for (auto &p : std::filesystem::recursive_directory_iterator(m_currentPath)) {
            m_assets.push_back({p.path(), false});
        }

        RType::Runtime::AssetManager::reset();
        RType::Runtime::AssetManager::init(g_projectInfos.path);
    }

    void AssetExplorer::f_openWithDefaultApp(const std::filesystem::path &path)
    {
        if (path.extension() == ".lua") {
            this->m_filePath = path;
            return;
        }

#ifdef _WIN32
        // FIXME: This is not working sometimes, for no apparent reason (yay)
        ShellExecute(0, 0, path.string().c_str(), 0, 0, SW_SHOW);
#elif __APPLE__
        system(("open " + path.string()).c_str());
#elif __linux__
        system(("xdg-open " + path.string()).c_str());
#endif
    }

    void AssetExplorer::f_createFile(const std::filesystem::path &path)
    {
        if (path.extension() != ".lua") {
            std::ofstream file(path);
            file.close();
            return;
        }

        std::ofstream file(path);
        std::ifstream templateFile("./assets/templates/template.lua");
        std::ifstream copyrightFile("./assets/templates/copyrightNotice.txt");

        if (!file.is_open() || !templateFile.is_open() || !copyrightFile) {
            EDITOR_LOG_ERROR("Failed to create file {0}", path.string().c_str());
            return;
        }

        std::string templateBuf((std::istreambuf_iterator<char>(templateFile)), std::istreambuf_iterator<char>());

        std::string copyrightLine;
        while (std::getline(copyrightFile, copyrightLine)) {
            file << "-- " << copyrightLine << "\n";
        }
        file << "\n";

        templateBuf.replace(templateBuf.find("{{ projectName }}"), 18, g_projectInfos.name + " ");
        templateBuf.replace(templateBuf.find("{{ filename }}"), 15, path.filename().string() + "\n");
        templateBuf.replace(templateBuf.find("{{ author }}"), 13, std::strcat(RType::Utils::getUsername(), "\n"));

        auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        templateBuf.replace(templateBuf.find("{{ date }}"), 11, std::ctime(&time));

        file << templateBuf;
        file.close();
        templateFile.close();
    }

} // namespace RType::Editor
