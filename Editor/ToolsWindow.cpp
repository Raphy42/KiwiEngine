//
// Created by Raphael DANTZER on 12/21/16.
//

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include "ToolsWindow.h"
#include "GlobalInstance.h"

void Kiwi::Editor::ToolsWindow::render() {
    if (!GlobalInstance::get().properties.getState("tools"))
        return;
    if (!ImGui::Begin("Tools", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::End();
        return;
    }
    if (ImGui::RadioButton("Rotate", _currentOperation == ImGuizmo::ROTATE))
        _currentOperation = ImGuizmo::ROTATE;
    ImGui::SameLine();
    if (ImGui::RadioButton("Translate", _currentOperation == ImGuizmo::TRANSLATE))
        _currentOperation = ImGuizmo::TRANSLATE;
    ImGui::SameLine();
    if (ImGui::RadioButton("Scale", _currentOperation == ImGuizmo::SCALE))
        _currentOperation = ImGuizmo::SCALE;
    static glm::mat4 transform;
    //TODO replace by actual entity
    ImGuizmo::DrawCube(glm::value_ptr(_camera->getViewMat4()), glm::value_ptr(_camera->getProjectionMat4()), glm::value_ptr(transform));
    process(transform);


    ImGui::End();
}

void Kiwi::Editor::ToolsWindow::process(glm::mat4 &transform) {
    float matrixTranslation[3], matrixRotation[3], matrixScale[3];

    ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(transform), matrixTranslation, matrixRotation, matrixScale);
    ImGui::InputFloat3("Position", matrixTranslation, 3);
    ImGui::InputFloat3("Rotation", matrixRotation, 3);
    ImGui::InputFloat3("Scale", matrixScale, 3);
    ImGuizmo::RecomposeMatrixFromComponents(matrixTranslation, matrixRotation, matrixScale, glm::value_ptr(transform));

    if (_currentOperation != ImGuizmo::SCALE) {
        if (ImGui::RadioButton("Local", _currentMode == ImGuizmo::LOCAL))
            _currentMode = ImGuizmo::LOCAL;
        ImGui::SameLine();
        if (ImGui::RadioButton("World", _currentMode == ImGuizmo::WORLD))
            _currentMode = ImGuizmo::WORLD;
    }

    static bool useSnap(false);
    if (ImGui::IsKeyPressed(83))
        useSnap = !useSnap;
    ImGui::Checkbox("", &useSnap);
    ImGui::SameLine();
    static glm::vec3 snap;
    switch (_currentOperation) {
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

    ImGuizmo::Manipulate(glm::value_ptr(_camera->getViewMat4()), glm::value_ptr(_camera->getProjectionMat4()),
                         _currentOperation, _currentMode, glm::value_ptr(transform), NULL, useSnap ? &snap.x : NULL);
    if (ImGuizmo::IsOver() || ImGuizmo::IsUsing())
        ImGui::SetMouseCursor(2);
}
