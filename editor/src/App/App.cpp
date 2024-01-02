/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** App
*/

#include "App.hpp"

namespace RType::Editor
{
    App::App()
    {
        m_window_ptr = std::unique_ptr<RType::Window::Window>(RType::Window::Window::Create());
        m_window_ptr->SetVSync(true);

        //m_window.create(sf::VideoMode(1920, 1080), "RType Editor");
        //m_window.setVerticalSyncEnabled(true);
        // ASSERT(ImGui::SFML::Init(m_window), "Failed to init ImGui")
        ASSERT(ImGui::SFML::Init(m_window_ptr->GetWindow()), "Failed to init ImGui")
        f_setStyle();

        m_layers.push_back(std::make_unique<InitDialog>());

        m_libHandle = RType::Utils::Modules::LoadSharedLibrary("runtime");
        ASSERT(m_libHandle, "Failed to load runtime library")

        RType::Runtime::IRuntime *(*runtimeEntry)() =
            (RType::Runtime::IRuntime * (*)()) RType::Utils::Modules::GetFunction(m_libHandle, "RuntimeEntry");
        ASSERT(runtimeEntry, "Failed to get runtime entry point")

        m_runtime = std::unique_ptr<RType::Runtime::IRuntime>(runtimeEntry());
    }

    App::~App()
    {
        ImGui::SFML::Shutdown();
    }

    void App::Run()
    {
        std::chrono::high_resolution_clock::time_point start;
        std::chrono::high_resolution_clock::time_point end;
        float fps = 0;

        while (m_window_ptr->GetWindow().isOpen()) {
            start = std::chrono::high_resolution_clock::now();
            while (m_window_ptr->GetWindow().pollEvent(m_event)) {
                ImGui::SFML::ProcessEvent(m_window_ptr->GetWindow(), m_event);
                if (m_event.type == sf::Event::Closed)
                    m_window_ptr->GetWindow().close();
            }
            ImGui::SFML::Update(m_window_ptr->GetWindow(), m_deltaClock.restart());
            ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

            f_checkShortcuts();
            f_checkForProjectLoading();
            for (auto &layer : m_layers) {
                layer->OnUpdate();
                layer->OnRender();
            }

            end = std::chrono::high_resolution_clock::now();
            fps = 1.0f / std::chrono::duration<float>(end - start).count();
            if (m_showDebugWindow) {
                ImGui::Begin("Debug");
                ImGui::Text("FPS: %.2f", fps);
                auto timers = m_runtime->getDebugTimes();
                ImGui::Text("Script time: %.2f ms", std::get<0>(timers));
                ImGui::Text("Render time: %.2f ms", std::get<1>(timers));
                ImGui::Text("Total time: %.2f ms", std::get<2>(timers));
                ImGui::End();
            }

            m_window_ptr->GetWindow().clear();
            ImGui::SFML::Render(m_window_ptr->GetWindow());
            m_window_ptr->GetWindow().display();
        }
        RType::Runtime::AssetManager::reset();
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
        m_runtime->Init(1920, 1080, g_projectInfos.path);
        m_runtime->setProjectPath(g_projectInfos.path);
        m_layers.push_back(std::make_unique<Viewport>(m_event, *m_runtime, m_runtime->GetRegistry()));
        m_layers.push_back(std::make_unique<AssetExplorer>());
        m_layers.push_back(std::make_unique<SceneHierarchy>(*m_runtime, m_runtime->GetRegistry()));
        m_layers.push_back(std::make_unique<Inspector>(*m_runtime, m_runtime->GetRegistry()));
        m_showToolbar = true;
    }

    void App::f_checkShortcuts()
    {
        static bool saveScene = false;
        static bool loadScene = false;
        static bool setDefaultScene = false;

        if (m_showToolbar && ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Save scene", "Ctrl+S")) {
                    saveScene = true;
                }
                if (ImGui::MenuItem("Load scene", "Ctrl+L")) {
                    loadScene = true;
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit")) {
                if (ImGui::MenuItem("Pause/Unpause", "Ctrl+P")) {
                    m_runtime->setPaused(!m_runtime->isPaused());
                }
                if (ImGui::MenuItem("Set default scene", "Ctrl+D")) {
                    setDefaultScene = true;
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Debug")) {
                if (ImGui::MenuItem("Debug window")) {
                    m_showDebugWindow = !m_showDebugWindow;
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        if ((ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_S)) && ImGui::GetIO().KeyCtrl) || saveScene)
            ImGui::OpenPopup("Save Scene");
        if (ImGui::BeginPopupModal("Save Scene", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
            static char sceneNameToSave[128] = {0};
            ImGui::InputText("Scene Name to save", sceneNameToSave, 128);
            if (ImGui::Button("Cancel")) {
                ImGui::CloseCurrentPopup();
                saveScene = false;
            }
            ImGui::SameLine();
            if (ImGui::Button("Save")) {
                ProjectManager::SaveProject(m_runtime, sceneNameToSave);
                saveScene = false;
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }

        if ((ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_L)) && ImGui::GetIO().KeyCtrl) || loadScene)
            ImGui::OpenPopup("Load Scene");
        if (ImGui::BeginPopupModal("Load Scene", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
            static char sceneNameToLoad[128] = {0};
            ImGui::InputText("Scene Name", sceneNameToLoad, 128);
            if (ImGui::Button("Cancel")) {
                loadScene = false;
                ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine();
            if (ImGui::Button("Load")) {
                ProjectManager::LoadProject(m_runtime, sceneNameToLoad);
                loadScene = false;
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }

        if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_P)) && ImGui::GetIO().KeyCtrl)
            m_runtime->setPaused(!m_runtime->isPaused());
        if ((ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_D)) && ImGui::GetIO().KeyCtrl) || setDefaultScene)
            ImGui::OpenPopup("Set default scene");

        if (ImGui::BeginPopupModal("Set default scene", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
            static char sceneNameToSet[128] = {0};
            ImGui::InputText("Scene Name", sceneNameToSet, 128);
            if (ImGui::Button("Cancel")) {
                ImGui::CloseCurrentPopup();
                setDefaultScene = false;
            }
            ImGui::SameLine();
            if (ImGui::Button("Set")) {
                std::fstream file(g_projectInfos.path + "/project.json", std::ios::in | std::ios::out);
                if (file.is_open()) {
                    json j;
                    file >> j;
                    j["startScene"] = "assets/scenes/" + std::string(sceneNameToSet) + ".json";
                    file.seekp(0);
                    file << std::setw(4) << j << std::endl;
                    file.close();
                }
                setDefaultScene = false;
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
    }
} // namespace RType::Editor
