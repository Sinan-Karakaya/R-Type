/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Inspector
*/

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
            } else if (ImGui::Selectable("Drawable")) {
                m_registry.AddComponent(g_currentEntitySelected,
                                        RType::Runtime::ECS::Components::Drawable {
                                            .sprite = sf::Sprite(), .texture = sf::Texture(), .clock = sf::Clock()});
                ImGui::CloseCurrentPopup();
            } else if (ImGui::Selectable("CircleShape")) {
                m_registry.AddComponent(g_currentEntitySelected,
                                        RType::Runtime::ECS::Components::CircleShape {.circle = sf::CircleShape()});
                ImGui::CloseCurrentPopup();
            } else if (ImGui::Selectable("Script")) {
                m_registry.AddComponent(g_currentEntitySelected,
                                        RType::Runtime::ECS::Components::Script {.clock = sf::Clock()});
                ImGui::CloseCurrentPopup();
            } else if (ImGui::Selectable("Controllable")) {
                m_registry.AddComponent(g_currentEntitySelected, RType::Runtime::ECS::Components::Controllable {});
                ImGui::CloseCurrentPopup();
            } else if (ImGui::Selectable("IAControllable")) {
                m_registry.AddComponent(g_currentEntitySelected, RType::Runtime::ECS::Components::IAControllable {});
                ImGui::CloseCurrentPopup();
            } else if (ImGui::Selectable("CollisionBox")) {
                m_registry.AddComponent(g_currentEntitySelected,
                                        RType::Runtime::ECS::Components::CollisionBox {.width = 0, .height = 0});
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
        ImGui::Separator();

        SKIP_EXCEPTIONS({ f_drawTagComponent(); })
        SKIP_EXCEPTIONS({ f_drawTransformComponent(); })
        SKIP_EXCEPTIONS({ f_drawRigidbodyComponent(); })
        SKIP_EXCEPTIONS({ f_drawDrawableComponent(); })
        SKIP_EXCEPTIONS({ f_drawCircleShapeComponent(); })
        SKIP_EXCEPTIONS({ f_drawScriptComponent(); })
        SKIP_EXCEPTIONS({ f_drawControllableComponent(); })
        SKIP_EXCEPTIONS({ f_drawIaControllableComponent(); })
        SKIP_EXCEPTIONS({ f_drawCollisionBoxComponent(); })

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
        auto &rb = m_registry.GetComponent<RType::Runtime::ECS::Components::RigidBody>(g_currentEntitySelected);
        ImGui::Text("Rigidbody");
        ImGui::DragFloat("Mass", &rb.mass, 0.1f);

        ImGui::Text("Velocity:");
        ImGui::DragFloat("##Velocity X", &rb.velocity.x, 0.1f);
        ImGui::DragFloat("##Velocity Y", &rb.velocity.y, 0.1f);

        ImGui::Text("Acceleration:");
        ImGui::DragFloat("##Acceleration X", &rb.acceleration.x, 0.1f);
        ImGui::DragFloat("##Acceleration Y", &rb.acceleration.y, 0.1f);

        ImGui::Checkbox("Use gravity", &rb.useGravity);
        ImGui::Checkbox("Is kinematic", &rb.isKinematic);
        ImGui::SameLine();
        if (ImGui::Button(ICON_FA_TRASH)) {
            m_registry.RemoveComponent<RType::Runtime::ECS::Components::RigidBody>(g_currentEntitySelected);
            return;
        }
        ImGui::Separator();
    }

    void Inspector::f_drawDrawableComponent()
    {
        auto &drawable = m_registry.GetComponent<RType::Runtime::ECS::Components::Drawable>(g_currentEntitySelected);
        ImGui::Text("Drawable");
        ImGui::SameLine();
        if (ImGui::Button(ICON_FA_TRASH)) {
            m_registry.RemoveComponent<RType::Runtime::ECS::Components::Drawable>(g_currentEntitySelected);
            return;
        }
        ImGui::InputText("Texture", drawable.path, 256);

        ImGui::Checkbox("Is collidable", &drawable.isCollidable);
        ImGui::Checkbox("Animated", &drawable.isAnimated);
        if (drawable.isAnimated) {
            ImGui::Checkbox("Autoplay", &drawable.autoPlay);
            ImGui::Text("Rect:");
            ImGui::DragFloat("Left", &drawable.rect.left, 0.1f);
            ImGui::DragFloat("Top", &drawable.rect.top, 0.1f);
            ImGui::DragFloat("Width", &drawable.rect.width, 0.1f);
            ImGui::DragFloat("Height", &drawable.rect.height, 0.1f);

            ImGui::NewLine();
            ImGui::DragInt("Frame count", &drawable.frameCount);
            ImGui::DragFloat("Frame duration", &drawable.frameDuration, 0.1f);
            ImGui::DragFloat("Frame decal X", &drawable.leftDecal, 0.1f);
            ImGui::DragFloat("Start position", &drawable.startPosition, 0.1f);
        }
        ImGui::Separator();
    }

    void Inspector::f_drawCircleShapeComponent()
    {
        auto &circleShape =
            m_registry.GetComponent<RType::Runtime::ECS::Components::CircleShape>(g_currentEntitySelected);
        ImGui::Text("CircleShape");
        ImGui::SameLine();
        if (ImGui::Button(ICON_FA_TRASH)) {
            m_registry.RemoveComponent<RType::Runtime::ECS::Components::CircleShape>(g_currentEntitySelected);
            return;
        }
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
        ImGui::SameLine();
        if (ImGui::Button(ICON_FA_TRASH)) {
            m_registry.RemoveComponent<RType::Runtime::ECS::Components::Script>(g_currentEntitySelected);
            return;
        }
        for (int i = 0; i < 6; i++) {
            ImGui::PushID(i);
            ImGui::InputText("Path", script.paths[i], 256);
            ImGui::PopID();
        }
        ImGui::Separator();
    }

    void Inspector::f_drawControllableComponent()
    {
        auto &controllable =
            m_registry.GetComponent<RType::Runtime::ECS::Components::Controllable>(g_currentEntitySelected);
        ImGui::Text("Controllable");
        ImGui::SameLine();
        if (ImGui::Button(ICON_FA_TRASH)) {
            m_registry.RemoveComponent<RType::Runtime::ECS::Components::Controllable>(g_currentEntitySelected);
            return;
        }
        ImGui::Checkbox("Is active", &controllable.isActive);
        ImGui::Checkbox("Is server controlled", &controllable.isServerControl);
        ImGui::Text("Inputs:");
        ImGui::SameLine();
        if (ImGui::Button(ICON_FA_PLUS " Add input")) {
            ImGui::OpenPopup("AddInput");
        }

        for (auto &input : controllable.inputs) {
            ImGui::Text("%s: ", input.first.c_str());
            ImGui::SameLine();
            ImGui::PushID(input.first.c_str());
            if (ImGui::Button(keyToStringMap.at(input.second).c_str())) {
                ImGui::OpenPopup("ChangeInput");
            }
            if (ImGui::BeginPopupContextItem("ChangeInput")) {
                for (int i = 0; i < sf::Keyboard::KeyCount; ++i) {
                    if (ImGui::Selectable(keyToStringMap.at(sf::Keyboard::Key(i)).c_str())) {
                        input.second = sf::Keyboard::Key(i);
                        ImGui::CloseCurrentPopup();
                    }
                }
                ImGui::EndPopup();
            }
            ImGui::SameLine();
            if (ImGui::Button(ICON_FA_TIMES)) {
                controllable.inputs.erase(input.first);
                ImGui::PopID();
                return;
            }
            ImGui::PopID();
        }

        if (ImGui::BeginPopupContextItem("AddInput")) {
            static char inputName[256] = "";
            ImGui::InputText("Name", inputName, 256);
            for (int i = 0; i < sf::Keyboard::KeyCount; ++i) {
                if (ImGui::Selectable(keyToStringMap.at(sf::Keyboard::Key(i)).c_str())) {
                    controllable.inputs[std::string(inputName)] = sf::Keyboard::Key(i);
                    ImGui::CloseCurrentPopup();
                }
            }

            ImGui::EndPopup();
        }
        ImGui::Separator();
    }

    void Inspector::f_drawTagComponent()
    {
        auto &tag = m_registry.GetComponent<RType::Runtime::ECS::Components::Tag>(g_currentEntitySelected);
        ImGui::InputText("Tag", tag.tag, 256);
        ImGui::SameLine();
        if (ImGui::Button(ICON_FA_DOWNLOAD)) {
            m_runtime.savePrefab(g_currentEntitySelected);
        }
        if (ImGui::Button(ICON_FA_UPLOAD)) {
            auto e = m_runtime.loadPrefab(tag.tag);
            m_runtime.RemoveEntity(g_currentEntitySelected);
            g_currentEntitySelected = e;
        }
        ImGui::Separator();
    }

    void Inspector::f_drawIaControllableComponent()
    {
        auto &iaControllable =
            m_registry.GetComponent<RType::Runtime::ECS::Components::IAControllable>(g_currentEntitySelected);
        ImGui::Text("IAControllable");
        ImGui::SameLine();
        if (ImGui::Button(ICON_FA_TRASH)) {
            m_registry.RemoveComponent<RType::Runtime::ECS::Components::IAControllable>(g_currentEntitySelected);
            return;
        }
        ImGui::Checkbox("Is active", &iaControllable.isActive);
        ImGui::InputText("Script", iaControllable.scriptPath, 256);
        ImGui::Separator();
    }

    void Inspector::f_drawCollisionBoxComponent()
    {
        auto &collisionBox =
            m_registry.GetComponent<RType::Runtime::ECS::Components::CollisionBox>(g_currentEntitySelected);
        ImGui::Text("CollisionBox");
        ImGui::SameLine();
        if (ImGui::Button(ICON_FA_TRASH)) {
            m_registry.RemoveComponent<RType::Runtime::ECS::Components::CollisionBox>(g_currentEntitySelected);
            return;
        }

        ImGui::Checkbox("Show Collision Box", &ShowUtils::showCollisionBoxes[g_currentEntitySelected]);

        ImGui::DragFloat("Box Width", &collisionBox.width, 0.0f);
        ImGui::DragFloat("Box Height", &collisionBox.height, 0.0f);
        ImGui::Separator();
    }

} // namespace RType::Editor
