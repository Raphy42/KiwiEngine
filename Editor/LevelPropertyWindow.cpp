//
// Created by Raphael DANTZER on 12/16/16.
//

#include <imgui.h>
#include "LevelPropertyWindow.h"
#include "GlobalInstance.h"
#include "../Engine/Assets/Loader.h"
#include "../Engine/GUI/Helper.h"

void
Kiwi::Editor::LevelPropertyWindow::render() {
    if (!GlobalInstance::get().properties.getState("properties"))
        return;

    ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiSetCond_FirstUseEver);
    if (!ImGui::Begin("Level properties", nullptr, ImGuiWindowFlags_AlwaysVerticalScrollbar)) {
        ImGui::End();
        return;
    }

    if (GlobalInstance::get().graph == nullptr) {
        static char buffer[256] = "default";
        ImGui::InputText("Name", buffer, 256);
        if (ImGui::Button("Create") && std::strlen(buffer)) {
            GlobalInstance::get().graph = new Kiwi::Engine::Scene::Graph;
            GlobalInstance::get().graph->setName(buffer);
        }
        ImGui::End();
        return;
    } else {

        ImGui::Text("Name: %s", GlobalInstance::get().graph->getName().c_str());
        ImGui::Text("Elements: %lu", GlobalInstance::get().graph->data().size());

        showEntityList();
    }

    ImGui::End();
}

void Kiwi::Editor::LevelPropertyWindow::showEntityList() const {
    static int selected = 0;

    ImGui::BeginChild("Entity list", ImVec2(150, 0), true);

    if (ImGui::Button("New")) {
        ImGui::OpenPopup("Add Entity");
    }
    addEntityToSceneDialog();

    int i = 0;
    for (const auto &node : GlobalInstance::get().graph->data())
        if (ImGui::Selectable(node->name.c_str(), selected == i++)) {
            selected = i;
        }

    ImGui::EndChild();
    ImGui::SameLine();

    // right

    if (selected)
        showEntityDetail(GlobalInstance::get().graph->data()[selected]);
}

void Kiwi::Editor::LevelPropertyWindow::addEntityToSceneDialog() const {
    if (!ImGui::BeginPopupModal("Add Entity"))
        return;

    static std::vector<Kiwi::Engine::Scene::GraphData *> cache;

    if (ImGui::Button("New Asset"))
        ImGui::OpenPopup("Load Asset");

    static int selected = -1;

    if (ImGui::BeginPopup("Load Asset")) {
        static fs::path path = ImGui::ListDirectoryEntries(fs::current_path().append("Assets"))
        if (path.extension() == "fbx") {
            Kiwi::Engine::Asset::Loader loader;
            auto graph = loader.createGraphFromModel(path.c_str());
            cache.insert(cache.end(), graph->data().begin(), graph->data.end());
        }
        ImGui::EndPopup();
    }

    ImGui::Text("Graph size %lu", cache.size());

    for (const auto &it : cache)
        if (ImGui::Selectable(it->name.c_str(), false))
            GlobalInstance::get().graph->add(

                    Kiwi::Engine::Scene::GraphFactory::create(it->mesh, it->material, it->bounds));

    if (ImGui::Button("Close"))
        ImGui::CloseCurrentPopup();
    ImGui::EndPopup();
}

void Kiwi::Editor::LevelPropertyWindow::showEntityDetail(Kiwi::Engine::Scene::GraphData *pData) const {
    ImGui::BeginGroup();
    ImGui::BeginChild(pData->name.c_str(),
                      ImVec2(0, -ImGui::GetItemsLineHeightWithSpacing())); // Leave room for 1 line below us
    ImGui::EndChild();
    ImGui::BeginChild("buttons");
    if (ImGui::Button("Save")) {}
    ImGui::EndChild();
    ImGui::EndGroup();
}
