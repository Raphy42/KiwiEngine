//
// Created by Raphael DANTZER on 12/21/16.
//

#ifndef KIWIENGINE_TOOLSWINDOW_H
#define KIWIENGINE_TOOLSWINDOW_H

#include <ImGuizmo.h>
#include "WindowInterface.h"
#include "../Engine/Primitives/Camera.h"
#include "../Engine/Scene/Graph.h"

namespace Kiwi {
    namespace Editor {
        class ToolsWindow : public WindowInterface {
        public:
            ToolsWindow() = default;
            ToolsWindow(Kiwi::Engine::Primitive::Camera *camera) : _camera(camera) {}
            virtual void render() override;

        private:
            void process(Kiwi::Engine::Scene::GraphData *data);

            ImGuizmo::OPERATION                 _currentOperation = ImGuizmo::ROTATE;
            ImGuizmo::MODE                      _currentMode = ImGuizmo::WORLD;
            Kiwi::Engine::Primitive::Camera     *_camera;
        };
    }
}


#endif //KIWIENGINE_TOOLSWINDOW_H
