//
// Created by Raphael DANTZER on 12/15/16.
//

#ifndef KIWIENGINE_EDITOR_H
#define KIWIENGINE_EDITOR_H

#include "../Engine/App.h"
#include "../Engine/Scene/Level.h"
#include "ImGuizmo.h"
#include "WindowInterface.h"

namespace kE = Kiwi::Engine;

namespace Kiwi { namespace Editor {
        class Editor : public Kiwi::Engine::App {
        public:
            Editor();

            void loop();
            void init();

        private:
            kE::Scene::Level                _level;
            kE::Primitive::FPSCamera        _camera;
            std::vector<WindowInterface *>  _windows;
        };
    }
}


#endif //KIWIENGINE_EDITOR_H
