//
// Created by Raphael DANTZER on 12/16/16.
//

#include <imgui.h>
#include "LevelPropertyWindow.h"
#include "GlobalInstance.h"

void Kiwi::Editor::LevelPropertyWindow::render() {
    if (g_globalInstance.state != State::SCENE_LOADED)
        return;

    if (!ImGui::Begin("Level properties", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::End();
        return;
    }

    ImGui::Text("Name: %s", g_globalInstance.world.get_name().c_str());

    ImGui::End();
}
