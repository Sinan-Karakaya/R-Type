/*
** EPITECH PROJECT, 2023
** Project
** File description:
** engine
*/

#include "imgui-SFML.h"
#include "imgui.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "Modules/modules.hpp"
#include "RType.hpp"

RType::Runtime::IRuntime *RuntimeEntry();
void RuntimeDestroy(RType::Runtime::IRuntime *runtime);

int main() {
    void *libHandle = RType::Utils::Modules::LoadSharedLibrary("libruntime");
    if (!libHandle) {
        RTYPE_LOG_CRITICAL("Failed to load runtime library");
        return 84;
    }

    RType::Runtime::IRuntime *(*runtimeEntry)() =
        (RType::Runtime::IRuntime * (*)()) RType::Utils::Modules::GetFunction(libHandle, "RuntimeEntry");
    if (!runtimeEntry) {
        RTYPE_LOG_CRITICAL("Failed to get runtime entry point");
        return 84;
    }

    RType::Runtime::IRuntime *runtime = runtimeEntry();
    if (!runtime) {
        RTYPE_LOG_CRITICAL("Failed to create runtime instance");
        return 84;
    }

    runtime->Init();
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "RType");
    window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(window);
    sf::Clock deltaClock;

    auto &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.ConfigWindowsMoveFromTitleBarOnly = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }
        ImGui::SFML::Update(window, deltaClock.restart());
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

        runtime->Update();
        runtime->Render();

        ImGui::Begin("Viewport");
        ImGui::Image(runtime->GetRenderTexture());
        if (ImGui::BeginDragDropTarget()) {
            if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("Asset")) {
                ImVec2 pos = ImGui::GetMousePos();
                ImVec2 winPos = ImGui::GetWindowPos();
                ImVec2 localPos = ImVec2(pos.x - winPos.x, pos.y - winPos.y);
                RTYPE_LOG_INFO("Accepted payload: {} at {} {}", (char *)payload->Data, localPos.x, localPos.y);
            }
            ImGui::EndDragDropTarget();
        }
        ImGui::End();

        ImGui::Begin("Asset Explorer");
        ImGui::End();

        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
