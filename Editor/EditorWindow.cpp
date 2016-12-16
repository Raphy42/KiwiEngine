//
// Created by Raphael DANTZER on 12/15/16.
//

#include "EditorWindow.h"


Kiwi::Editor::EditorWindow::EditorWindow() : Kiwi::Editor::WindowInterface() {
    _recentFiles = g_globalInstance.editorConfig.getVector<std::string>("recent_files");
    _flags["file_creation"] = false;
    _flags["file_opening"] = false;
    _flags["error"] = false;
}

Kiwi::Editor::EditorWindow::~EditorWindow() {

}

void Kiwi::Editor::EditorWindow::render() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            fileDialog();
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}
            ImGui::EndMenu();
        }
        if (_flags["error"])
            ImGui::MenuItem("Error log", _lastError);
        ImGui::EndMainMenuBar();
    }
    if (_flags["file_creation"])
        fileCreation(&_flags["file_creation"]);
    if (_flags["file_opening"])
        fileOpen(&_flags["file_opening"]);

}

void Kiwi::Editor::EditorWindow::fileDialog() {
    ImGui::MenuItem("New", nullptr, &_flags["file_creation"]);
    ImGui::MenuItem("Open", "Ctrl+O", &_flags["file_opening"]);
    if (ImGui::BeginMenu("Open Recent")) {
        if (_recentFiles.size())
            for (const auto &it : _recentFiles)
                ImGui::MenuItem(it.c_str());
        else
            ImGui::MenuItem("No recent files");
        ImGui::EndMenu();
    }
    if (ImGui::MenuItem("Save", "Ctrl+S")) {}
    if (ImGui::MenuItem("Save As..")) {}
    ImGui::Separator();
    if (ImGui::MenuItem("Quit")) { exit(EXIT_SUCCESS); }
}

void Kiwi::Editor::EditorWindow::fileCreation(bool *p_open) {
    if (!ImGui::Begin("Create new file", p_open, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::End();
        return;
    }

    static bool file_exists_already = false, override = false;
    static char buffer[256] = "";
    static int current = -1;
    const char *items[] = {"Scene", "Other"};

    if (file_exists_already) {
        ImGui::Text("File already exists");
        if (ImGui::Button("Override"))
            std::cout << "File overwritten" << std::endl;
    }
    ImGui::InputText("Filename", buffer, 256);
    ImGui::Combo("Type", &current, items, 2);

    if (std::strlen(buffer) && current != -1 && !file_exists_already) if (ImGui::Button("Create")) {
        std::string path = g_globalInstance.vfs.getFilename(std::make_pair("textures", std::string(buffer)));
        if (g_globalInstance.vfs.exists(path))
            file_exists_already = true;
        else
            *p_open = false;
    }

    ImGui::End();
}

void Kiwi::Editor::EditorWindow::fileOpen(bool *p_open) {
    if (!ImGui::Begin("Open file", p_open, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::End();
        return;
    }

    static std::vector<fs::path> files;
    static fs::path current;

    if (files.size() == 0) {
        files = g_globalInstance.vfs.getDirectoryEntries("levels");
    }

    if (ImGui::BeginMenu(current.filename().size() ? current.filename().c_str() : "Select one")) {
        for (const auto &file : files)
            if (ImGui::MenuItem(file.filename().c_str(), file.relative_path().c_str()))
                current = file;
        ImGui::EndMenu();
    }

    if (current.filename().size()) {
        if (ImGui::Button("Open")) {
            try {
                g_globalInstance.levelConfig = Core::JSONConfig(current.string());
                g_globalInstance.state = State::SCENE_OPENED;
                _flags["file_opening"] = false;
            } catch (const std::exception &e) {
                _flags["error"] = true;
                std::cout << e.what() << std::endl;
            }
        }
    }

    ImGui::End();
}

