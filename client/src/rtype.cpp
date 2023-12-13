/*
** EPITECH PROJECT, 2023
** Project
** File description:
** client
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Modules/modules.hpp"
#include "RType.hpp"
#include "Runtime/IRuntime.hpp"

RType::Runtime::IRuntime *RuntimeEntry();
void RuntimeDestroy(RType::Runtime::IRuntime *runtime);

int main()
{
    void *libHandle = RType::Utils::Modules::LoadSharedLibrary("runtime");
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

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
            if (event.type == sf::Event::Resized)
                runtime->HandleResizeEvent(event);
        }

        window.clear();

        runtime->Update(event);
        runtime->Render();

        window.draw(runtime->GetRenderTextureSprite());

        window.display();
    }

    return 0;
}
