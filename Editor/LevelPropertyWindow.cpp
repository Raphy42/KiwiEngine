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

void Kiwi::Editor::LevelPropertyWindow::showEntityList() {
    static int selected = 0;

    ImGui::BeginChild("Entity list", ImVec2(150, 0), true);

    if (ImGui::Button("New")) {
        ImGui::OpenPopup("Add Entity");
    }
    addEntityToSceneDialog();

    static Kiwi::Engine::Scene::GraphData *data = nullptr;
    ImGui::ListGraphEntries(GlobalInstance::get().graph, [&](Kiwi::Engine::Scene::GraphData *graph) {
        data = graph;
    });
    ImGui::EndChild();
    ImGui::SameLine();
    if (data)
        showEntityDetail(data);

}

void Kiwi::Editor::LevelPropertyWindow::addEntityToSceneDialog() {
    ImGui::SetNextWindowSize(ImVec2(500, 500));
    if (!ImGui::BeginPopupModal("Add Entity"))
        return;

    if (ImGui::Button("New Asset"))
        ImGui::OpenPopup("Load Asset");

    static int selected = -1;

    if (ImGui::BeginPopup("Load Asset")) {
        ImGui::ListDirectoryEntries(fs::current_path().append("Assets"), [&](fs::path path) {
            Kiwi::Engine::Asset::Loader loader;
            if (loader.isValidFile(path)) {
                auto graph = loader.createGraphFromModel(path.c_str());
                _cache.push_back(graph);
            }
        });
        ImGui::EndPopup();
    }

    ImGui::Text("Graph size %lu", _cache.size());

    for (const auto &it : _cache)
        ImGui::ListGraphEntries(it, [](Kiwi::Engine::Scene::GraphData *graph) {
            auto node = Kiwi::Engine::Scene::GraphFactory::create(graph->mesh, graph->material, graph->bounds);
            node->name = graph->name;
            GlobalInstance::get().graph->add(node);
        });

    if (ImGui::Button("Close"))
        ImGui::CloseCurrentPopup();
    ImGui::EndPopup();
}

void Kiwi::Editor::LevelPropertyWindow::showEntityDetail(Kiwi::Engine::Scene::GraphData *pData) const {
    ImGui::BeginGroup();
    ImGui::BeginChild(pData->name.c_str(),
                      ImVec2(0, -ImGui::GetItemsLineHeightWithSpacing()));
    ImGui::Text("%s", pData->name.c_str());
    ImGui::Text("Shader id %lu", pData->material->getType());
    if (pData->material->getType() == Kiwi::Engine::Renderer::Shading::Type::PHONG)
        ImGui::PhongMaterialEditor(static_cast<Kiwi::Engine::Renderer::PhongMaterial *>(pData->material));

    ImGui::Separator();
    ImGui::Manipulate(pData, GlobalInstance::get().cache.camera);
    ImGui::EndChild();
    ImGui::BeginChild("buttons");
    if (ImGui::Button("Save")) {}
    ImGui::EndChild();
    ImGui::EndGroup();
}
