//
// Created by Raphael DANTZER on 12/15/16.
//

#ifndef KIWIENGINE_PROPERTYWINDOW_H
#define KIWIENGINE_PROPERTYWINDOW_H

#include <imgui.h>
#include <cstdio>
#include <string>
#include <vector>
#include <unordered_map>
#include "WindowInterface.h"
#include "GlobalInstance.h"

namespace Kiwi { namespace Editor {
        class EditorWindow : public WindowInterface {
        public:
            EditorWindow();
            ~EditorWindow();

            void render() override;

        private:
            void fileDialog();

            std::vector<std::string>                _recentFiles;

            void                                    fileCreation(bool *p_open);
            void                                    fileOpen(bool *p_open);

            const char                              *_lastError;
        };
    }
}

#endif //KIWIENGINE_PROPERTYWINDOW_H
