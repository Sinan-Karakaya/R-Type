/*
** EPITECH PROJECT, 2023
** Project
** File description:
** engine
*/

#include "Editor.hpp"
#include "App/App.hpp"

project_t g_projectInfos = {"", "", false, false};

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    (void)hInstance;
    (void)hPrevInstance;
    (void)lpCmdLine;
    (void)nCmdShow;

    RType::Editor::App app;
    app.Run();

    return 0;
}
#else
int main() {
    RType::Editor::App app;
    app.Run();

    return 0;
}
#endif
