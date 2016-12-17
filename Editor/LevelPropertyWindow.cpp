//
// Created by Raphael DANTZER on 12/16/16.
//

#include <imgui.h>
#include "LevelPropertyWindow.h"
#include "GlobalInstance.h"

void Kiwi::Editor::LevelPropertyWindow::render() {
    if (GlobalInstance::get().state < State::SCENE_LOADED)
        return;

    if (!ImGui::Begin("Level properties", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::End();
        return;
    }

    static char buffer[256] = "default";

    ImGui::Text("%s", GlobalInstance::get().world.get_name().c_str());
//    ImGui::InputText("World name", buffer, 256);
//    static std::vector<float> transform;
//    for (const auto &var : transform)
//        ImGui::Text("%f", var);

    ImGui::End();
}
