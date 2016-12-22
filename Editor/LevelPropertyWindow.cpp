//
// Created by Raphael DANTZER on 12/16/16.
//

#include <imgui.h>
#include "LevelPropertyWindow.h"
#include "GlobalInstance.h"

void Kiwi::Editor::LevelPropertyWindow::render() {
    if (!GlobalInstance::get().properties.getState("properties"))
        return;

    if (!ImGui::Begin("Level properties", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::End();
        return;
    }



    ImGui::End();
}
