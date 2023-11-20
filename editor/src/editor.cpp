/*
** EPITECH PROJECT, 2023
** Project
** File description:
** engine
*/

#include "App/App.hpp"
#include "Modules/modules.hpp"

RType::Runtime::IRuntime *RuntimeEntry();
void RuntimeDestroy(RType::Runtime::IRuntime *runtime);

int main() {
    void *libHandle = RType::Utils::Modules::LoadSharedLibrary("libruntime");
    ASSERT(libHandle, "Failed to load runtime library")

    RType::Runtime::IRuntime *(*runtimeEntry)() =
        (RType::Runtime::IRuntime * (*)()) RType::Utils::Modules::GetFunction(libHandle, "RuntimeEntry");
    ASSERT(runtimeEntry, "Failed to get runtime entry point")

    RType::Editor::App app(runtimeEntry);

    app.Run();

    ASSERT(RType::Utils::Modules::FreeSharedLibrary(libHandle), "Failed to free runtime library")
    return 0;
}
