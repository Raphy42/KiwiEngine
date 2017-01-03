//
// Created by Raphaël Dantzer on 03/01/17.
//

#ifndef KIWIENGINE_HELPER_H
#define KIWIENGINE_HELPER_H

/**
 * Helpers for Imgui
 */
#include <imgui.h>
#include "../../Core/Filesystem/VirtualFilesystem.h"

namespace ImGui {
    inline fs::path         ListDirectoryEntries(const fs::path &path) {
        if (ImGui::BeginMenu(path.filename().c_str())) {
            for (fs::directory_iterator entry(path); entry != fs::directory_iterator(); ++entry) {
                fs::path tmp_path = entry->path();
                if (fs::is_directory(tmp_path)) {
                    if (ImGui::BeginMenu(tmp_path.filename().c_str())) {
                        ListDirectoryEntries(tmp_path);
                        ImGui::EndMenu();
                    }
                } else {
                    if (ImGui::MenuItem(tmp_path.filename().c_str()))
                        return tmp_path;
                }
            }
            ImGui::EndMenu();
        }
        return fs::path();
    }
}

#endif //KIWIENGINE_HELPER_H
