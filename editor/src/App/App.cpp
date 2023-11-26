#include "App.hpp"

namespace RType::Editor
{
    App::App()
    {
        m_window.create(sf::VideoMode(1920, 1080), "RType Editor");
        m_window.setVerticalSyncEnabled(true);
        ASSERT(ImGui::SFML::Init(m_window), "Failed to init ImGui")
        f_setStyle();

        m_layers.push_back(std::make_unique<InitDialog>());
    }

    void App::Run()
    {
        while (m_window.isOpen()) {
            while (m_window.pollEvent(m_event)) {
                ImGui::SFML::ProcessEvent(m_window, m_event);
                if (m_event.type == sf::Event::Closed)
                    m_window.close();
            }
            ImGui::SFML::Update(m_window, m_deltaClock.restart());
            ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

            f_checkForProjectLoading();
            for (auto &layer : m_layers) {
                layer->OnUpdate();
                layer->OnRender();
            }

            m_window.clear();
            ImGui::SFML::Render(m_window);
            m_window.display();
        }
    }

    void App::f_checkForProjectLoading()
    {
        if (g_projectInfos.shouldLoad && !g_projectInfos.shouldCreate) {
            m_layers.clear();
            ASSERT(m_layers.empty(), "Layers should be empty")
            ProjectManager::LoadProject();
            f_setupDevLayers();
        } else if (g_projectInfos.shouldCreate && g_projectInfos.shouldLoad) {
            m_layers.clear();
            ASSERT(m_layers.empty(), "Layers should be empty")
            ProjectManager::CreateProject();
            f_setupDevLayers();
        }
    }

    void App::f_setStyle()
    {
        ImGuiIO &io = ImGui::GetIO();
        io.IniFilename = "./assets/imgui.ini";
        io.Fonts->Clear();
        io.Fonts->AddFontFromFileTTF("./assets/Roboto.ttf", 16);
        ASSERT(ImGui::SFML::UpdateFontTexture(), "Failed to update font texture")
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows

        ImFontConfig config;
        config.MergeMode = true;
        config.GlyphMinAdvanceX = 13.0f; // Use if you want to make the icon monospaced
        static const ImWchar icon_ranges[] = {ICON_MIN_FA, ICON_MAX_FA, 0};
        io.Fonts->AddFontFromFileTTF("./assets/fontawesome-webfont.ttf", 16.0f, &config, icon_ranges);
        ASSERT(ImGui::SFML::UpdateFontTexture(), "Failed to update font texture")

        ImVec4 *colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_WindowBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
        colors[ImGuiCol_ChildBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
        colors[ImGuiCol_FrameBg] = ImVec4(0.25f, 0.25f, 0.25f, 0.54f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.50f, 0.50f, 0.50f, 0.40f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.54f, 0.54f, 0.54f, 0.67f);
        colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_MenuBarBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_CheckMark] = ImVec4(0.97f, 0.97f, 0.97f, 1.00f);
        colors[ImGuiCol_SliderGrab] = ImVec4(0.57f, 0.57f, 0.57f, 1.00f);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(0.77f, 0.77f, 0.77f, 1.00f);
        colors[ImGuiCol_Button] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
        colors[ImGuiCol_Header] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
        colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
        colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.98f, 0.98f, 0.98f, 0.67f);
        colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.95f);
        colors[ImGuiCol_Tab] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
        colors[ImGuiCol_TabHovered] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
        colors[ImGuiCol_TabActive] = ImVec4(0.48f, 0.48f, 0.48f, 1.00f);
        colors[ImGuiCol_DockingPreview] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    }

    void App::f_setupDevLayers()
    {
        m_layers.push_back(std::make_unique<Viewport>());
        m_layers.push_back(std::make_unique<AssetExplorer>());
        m_layers.push_back(std::make_unique<SceneHierarchy>());
        m_layers.push_back(std::make_unique<Inspector>());
    }
} // namespace RType::Editor
