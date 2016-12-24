//
// Created by Raphael DANTZER on 12/16/16.
//

#include <imgui.h>
#include "LevelPropertyWindow.h"
#include "GlobalInstance.h"
#include "../Engine/Assets/Loader.h"
#include "../Engine/Scene/Graph.h"
#include "../Engine/Renderer/PhongMaterial.h"

void
Kiwi::Editor::LevelPropertyWindow::render() {
    if (!GlobalInstance::get().properties.getState("properties"))
        return;

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
    }

    ImGui::Text("Name: %s", GlobalInstance::get().graph->getName().c_str());
    ImGui::Text("Elements: %lu", GlobalInstance::get().graph->data().size());

    static std::vector<fs::path> paths;

    if (paths.size() == 0)
        paths = GlobalInstance::get().vfs.getDirectoryEntries("models");

    if (ImGui::BeginMenu("Load asset")) {
        if (paths.size()) {
            for (const auto &it : paths) {
                if (ImGui::MenuItem(it.c_str())) {
                    static Kiwi::Engine::Asset::Loader loader;
                    _assets.push_back(loader.createGraphFromModel(it.c_str(), it.filename().string()));
                }

            }
        } else {
            ImGui::MenuItem("No files");
        }
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Assets")) {
        if (_assets.size()) {
            for (auto &it : _assets) {
                if (ImGui::MenuItem(it->getName().c_str())) {
                    for (auto &asset : it->data())
                        GlobalInstance::get().graph->add(asset);
                }
            }
        }
        ImGui::EndMenu();
    }

    ImGui::PushStyleVar(ImGuiStyleVar_ChildWindowRounding, 5.0f);
    ImGui::Columns(1);
    for (const auto &it : GlobalInstance::get().graph->data())
        if (ImGui::Button(it->name.c_str(), ImVec2(-1.f, 0.f))) {
            GlobalInstance::get().cache.selection.clear(); //todo this is quite dirty but it does the job
            GlobalInstance::get().cache.selection.push_back(it);
        }
    ImGui::PopStyleVar();

    ImGui::End();
}
