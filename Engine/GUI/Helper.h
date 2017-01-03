//
// Created by Raphaël Dantzer on 03/01/17.
//

#ifndef KIWIENGINE_HELPER_H
#define KIWIENGINE_HELPER_H

/**
 * Helpers for Imgui
 */
#include <imgui.h>
#include <ImGuizmo.h>
#include <glm/gtc/type_ptr.hpp>
#include "../../Core/Filesystem/VirtualFilesystem.h"
#include "../Renderer/PhongMaterial.h"
#include "../Renderer/PhongTexturedMaterial.h"

namespace ImGui {
    template<typename L>
    inline void ListDirectoryEntries(const boost::filesystem::path &path, L lambda) {
        if (ImGui::BeginMenu(path.filename().c_str())) {
            for (fs::directory_iterator entry(path); entry != fs::directory_iterator(); ++entry) {
                fs::path tmp_path = entry->path();
                if (fs::is_directory(tmp_path)) {
                    if (ImGui::BeginMenu(tmp_path.filename().c_str())) {
                        ListDirectoryEntries(tmp_path, lambda);
                        ImGui::EndMenu();
                    }
                } else {
                    if (ImGui::MenuItem(tmp_path.filename().c_str())) {
                        ImGui::EndMenu();
                        return lambda(tmp_path);
                    }
                }
            }
            ImGui::EndMenu();
        }
    }

    template<typename L>
    inline void ListGraphEntries(const Kiwi::Engine::Scene::Graph *graph, L lambda) {
        if (ImGui::BeginMenu(graph->getName().c_str())) {
            for (const auto &entry : graph->data())
                if (ImGui::MenuItem(entry->name.c_str()))
                    lambda(entry);
            if (!graph->data().size())
                ImGui::Text("No items");
            ImGui::EndMenu();
        }
    }

    inline void Manipulate(Kiwi::Engine::Scene::GraphData *data, Kiwi::Engine::Primitive::FPSCamera *camera) {
        float matrixTranslation[3], matrixRotation[3], matrixScale[3];

        glm::mat4 transform = data->actuator->update();

        ImGui::Text(data->name.c_str());

        ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(transform), matrixTranslation, matrixRotation,
                                              matrixScale);
        ImGui::InputFloat3("Position", matrixTranslation, 3);
        ImGui::InputFloat3("Rotation", matrixRotation, 3);
        ImGui::InputFloat3("Scale", matrixScale, 3);
        data->actuator->recompose(matrixTranslation, matrixRotation, matrixScale);
        static ImGuizmo::OPERATION currentOperation;
        static ImGuizmo::MODE currentMode;

        if (ImGui::RadioButton("Rotate", currentOperation == ImGuizmo::ROTATE))
            currentOperation = ImGuizmo::ROTATE;
        ImGui::SameLine();
        if (ImGui::RadioButton("Translate", currentOperation == ImGuizmo::TRANSLATE))
            currentOperation = ImGuizmo::TRANSLATE;
        ImGui::SameLine();
        if (ImGui::RadioButton("Scale", currentOperation == ImGuizmo::SCALE))
            currentOperation = ImGuizmo::SCALE;

        if (currentOperation != ImGuizmo::SCALE) {
            if (ImGui::RadioButton("Local", currentMode == ImGuizmo::LOCAL))
                currentMode = ImGuizmo::LOCAL;
            ImGui::SameLine();
            if (ImGui::RadioButton("World", currentMode == ImGuizmo::WORLD))
                currentMode = ImGuizmo::WORLD;
        }

        static bool useSnap(false);
        if (ImGui::IsKeyPressed(83))
            useSnap = !useSnap;
        ImGui::Checkbox("", &useSnap);
        ImGui::SameLine();
        static glm::vec3 snap;
        switch (currentOperation) {
            case ImGuizmo::TRANSLATE:
                ImGui::InputFloat3("Snap", glm::value_ptr(snap));
                break;
            case ImGuizmo::ROTATE:
                ImGui::InputFloat("Angle Snap", glm::value_ptr(snap));
                break;
            case ImGuizmo::SCALE:
                ImGui::InputFloat("Scale Snap", glm::value_ptr(snap));
                break;
        }
        ImGuizmo::Manipulate(glm::value_ptr(camera->getViewMat4()), glm::value_ptr(camera->getProjectionMat4()),
                             currentOperation, currentMode, glm::value_ptr(transform), NULL, useSnap ? &snap.x : NULL);
        data->actuator->recompose(transform);

        if (ImGuizmo::IsOver() || ImGuizmo::IsUsing())
            ImGui::SetMouseCursor(2);
    }

    inline void PhongMaterialEditor(Kiwi::Engine::Renderer::PhongMaterial *material) {
        static float color[4] = {material->_color.x, material->_color.y, material->_color.y, 1.f};
        ImGui::ColorButton({material->_color.x, material->_color.y, material->_color.y, 1.f});
        if (ImGui::BeginPopupContextItem("color context menu"))
        {
            ImGui::Text("Edit color");
            ImGui::ColorEdit3("##edit", &color[0]);
            if (ImGui::Button("Close"))
                material->setColor(glm::make_vec3(color));
                ImGui::CloseCurrentPopup();
            ImGui::EndPopup();
        }
    }
}

#endif //KIWIENGINE_HELPER_H
