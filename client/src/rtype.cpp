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

    /*
    auto rectangle = sf::RectangleShape(sf::Vector2f(100, 100));
    rectangle.setFillColor(sf::Color::Red);
    RType::Runtime::ECS::Components::UIRectangleElement uiRectangle = {
        .rectangle = rectangle,
        .text = "Hello, World"
        // .text = sf::Text("Hello World", sf::Font::GetDefaultFont(), 50)
    };
    */
    
    auto &registry = runtime->GetRegistry();

    sf::CircleShape circle(30);
    circle.setOutlineThickness(10);
    circle.setOutlineColor(sf::Color(250, 150, 100));
    circle.setFillColor(sf::Color(150, 50, 250));
    circle.setPosition(500, 650);


    RType::Runtime::ECS::Entity circleEntity = runtime->AddEntity();

    registry.AddComponent(circleEntity, RType::Runtime::ECS::Components::CircleShape {
        .circle = circle
    });


    sf::RectangleShape rectangle(sf::Vector2f(100, 100));
    rectangle.setOutlineColor(sf::Color(250, 150, 100));
    rectangle.setFillColor(sf::Color(150, 50, 250));
    rectangle.setPosition(0, 0);

    sf::Font font;

    font.loadFromFile("assets/Roboto.ttf");

    sf::Text text("Hello World", font);
    text.setPosition(100, 150);
    text.setFillColor(sf::Color::Red);
    text.setCharacterSize(30);

    RType::Runtime::ECS::Entity rectangleEntity = runtime->AddEntity();

    registry.AddComponent(rectangleEntity, RType::Runtime::ECS::Components::Transform {
        .position = { 0, 0 },
        .rotation = {0, 0},
        .scale = { 1, 1 }
    });

    registry.AddComponent(rectangleEntity, RType::Runtime::ECS::Components::UIRectangleElement {
        .rectangle = rectangle,
        .text = text
    });



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
