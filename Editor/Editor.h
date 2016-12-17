//
// Created by Raphael DANTZER on 12/15/16.
//

#ifndef KIWIENGINE_EDITOR_H
#define KIWIENGINE_EDITOR_H

#include "../Engine/App.h"
#include "../Engine/Scene/Level.h"
#include "ImGuizmo.h"
#include "WindowInterface.h"
#include "../Engine/Renderer/CubeMaterial.h"
#include "../Engine/Assets/Loader.h"
#include "EditorWindow.h"

namespace kE = Kiwi::Engine;

namespace Kiwi { namespace Editor {
        class Editor : public Kiwi::Engine::App {
        public:
            Editor();

            void loop();
            void init();
            void processEvent();

        private:
            kE::Scene::Level                _level;
            kE::Primitive::FPSCamera        _camera;
            std::vector<WindowInterface *>  _windows;
            Engine::Scene::Entity           _defaultSkybox;
        };
    }
}


#endif //KIWIENGINE_EDITOR_H
