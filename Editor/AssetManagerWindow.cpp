//
// Created by Raphael DANTZER on 1/3/17.
//

#include <imgui.h>
#include "AssetManagerWindow.h"
#include "GlobalInstance.h"
#include "../Engine/GUI/Helper.h"

void Kiwi::Editor::AssetManagerWindow::render() {
    ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiSetCond_FirstUseEver);
    if (!ImGui::Begin("Asset browser", nullptr, ImGuiWindowFlags_AlwaysVerticalScrollbar)) {
        ImGui::End();
        return;
    }

    ImGui::ListDirectoryEntries(fs::current_path(), [](fs::path selected){});

    ImGui::End();
}
