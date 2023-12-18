#include "Inspector.hpp"

namespace RType::Editor
{
    void Inspector::OnAttach() {}
    void Inspector::OnDetach() {}
    void Inspector::OnUpdate() {}
    void Inspector::OnRender()
    {
        if (g_currentEntitySelected == -1) {
            ImGui::Begin("Inspector");
            ImGui::End();
            return;
        }

        ImGui::Begin("Inspector");
        ImGui::Text("Entity: %d", g_currentEntitySelected);
        ImGui::SameLine();
        if (ImGui::Button(ICON_FA_PLUS " Add component")) {
            ImGui::OpenPopup("AddComponent");
        }
        if (ImGui::BeginPopupContextItem("AddComponent")) {
            if (ImGui::Selectable("Rigibody")) {
                m_registry.AddComponent(g_currentEntitySelected, RType::Runtime::ECS::Components::RigidBody {
                                                                     .velocity = {0, 0}, .acceleration = {0, 0}});
                ImGui::CloseCurrentPopup();
            } else if (ImGui::Selectable("Gravity")) {
                m_registry.AddComponent(g_currentEntitySelected,
                                        RType::Runtime::ECS::Components::Gravity {.force = {0, 0}});
                ImGui::CloseCurrentPopup();
            } else if (ImGui::Selectable("Drawable")) {
                m_registry.AddComponent(g_currentEntitySelected, RType::Runtime::ECS::Components::Drawable {
                                                                     .sprite = sf::Sprite(), .texture = sf::Texture()});
                ImGui::CloseCurrentPopup();
            } else if (ImGui::Selectable("CircleShape")) {
                m_registry.AddComponent(g_currentEntitySelected,
                                        RType::Runtime::ECS::Components::CircleShape {.circle = sf::CircleShape()});
                ImGui::CloseCurrentPopup();
            } else if (ImGui::Selectable("Script")) {
                m_registry.AddComponent(g_currentEntitySelected, RType::Runtime::ECS::Components::Script {});
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
        ImGui::Separator();

        try {
            f_drawTransformComponent();
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
        try {
            f_drawRigidbodyComponent();
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
        try {
            f_drawDrawableComponent();
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
        try {
            f_drawGravityComponent();
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
        try {
            f_drawCircleShapeComponent();
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
        try {
            f_drawScriptComponent();
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }

        ImGui::End();
    }

    void Inspector::f_drawTransformComponent()
    {
        auto &transform = m_registry.GetComponent<RType::Runtime::ECS::Components::Transform>(g_currentEntitySelected);
        ImGui::Text("Transform");

        ImGui::Text("Position:");
        ImGui::DragFloat("X##pos", &transform.position.x, 0.1f);
        ImGui::DragFloat("Y##pos", &transform.position.y, 0.1f);

        ImGui::Text("Rotation:");
        ImGui::DragFloat("##", &transform.rotation.x, 0.1f);

        ImGui::Text("Scale:");
        ImGui::DragFloat("X##scale", &transform.scale.x, 0.1f);
        ImGui::DragFloat("Y##scale", &transform.scale.y, 0.1f);

        ImGui::Separator();
    }

    void Inspector::f_drawRigidbodyComponent()
    {
        auto &rigidbody = m_registry.GetComponent<RType::Runtime::ECS::Components::RigidBody>(g_currentEntitySelected);
        ImGui::Text("Rigidbody");
        ImGui::Separator();
    }

    void Inspector::f_drawDrawableComponent()
    {
        auto &drawable = m_registry.GetComponent<RType::Runtime::ECS::Components::Drawable>(g_currentEntitySelected);
        ImGui::Text("Drawable");
        ImGui::InputText("Texture", drawable.path, 256);

        ImGui::Checkbox("Animated", &drawable.isAnimated);
        if (drawable.isAnimated) {
            ImGui::DragFloat("Left", &drawable.rect.left, 0.1f);
            ImGui::DragFloat("Top", &drawable.rect.top, 0.1f);
            ImGui::DragFloat("Width", &drawable.rect.width, 0.1f);
            ImGui::DragFloat("Height", &drawable.rect.height, 0.1f);
            drawable.firstFrameRect = drawable.rect;

            ImGui::DragInt("Frame count", &drawable.frameCount, 1);
            ImGui::DragFloat("Frame duration", &drawable.frameDuration, 0.1f);
            ImGui::DragFloat("Frame decal X", &drawable.leftDecal, 0.1f);
        }
        ImGui::Separator();
    }

    void Inspector::f_drawGravityComponent()
    {
        auto &gravity = m_registry.GetComponent<RType::Runtime::ECS::Components::Gravity>(g_currentEntitySelected);
        ImGui::Text("Gravity");
        ImGui::DragFloat("Force X", &gravity.force.x, 0.1f);
        ImGui::DragFloat("Force Y", &gravity.force.y, 0.1f);
        ImGui::Separator();
    }

    void Inspector::f_drawCircleShapeComponent()
    {
        auto &circleShape =
            m_registry.GetComponent<RType::Runtime::ECS::Components::CircleShape>(g_currentEntitySelected);
        ImGui::Text("CircleShape");
        static float radius = circleShape.circle.getRadius();
        ImGui::DragFloat("Radius", &radius, 0.1f);
        circleShape.circle.setRadius(radius);

        float color[3] = {static_cast<float>(circleShape.circle.getFillColor().r) / 255.0f,
                          static_cast<float>(circleShape.circle.getFillColor().g) / 255.0f,
                          static_cast<float>(circleShape.circle.getFillColor().b) / 255.0f};

        ImGui::ColorPicker3("Color", color);
        circleShape.circle.setFillColor(sf::Color(static_cast<sf::Uint8>(color[0] * 255.0f),
                                                  static_cast<sf::Uint8>(color[1] * 255.0f),
                                                  static_cast<sf::Uint8>(color[2] * 255.0f)));
        ImGui::Separator();
    }

    void Inspector::f_drawScriptComponent()
    {
        auto &script = m_registry.GetComponent<RType::Runtime::ECS::Components::Script>(g_currentEntitySelected);
        ImGui::Text("Script");
        ImGui::InputText("Path", script.path, 256);
        ImGui::Separator();
    }
} // namespace RType::Editor
