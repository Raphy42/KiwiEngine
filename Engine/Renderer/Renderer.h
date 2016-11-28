//
// Created by Raphaël Dantzer on 26/11/16.
//

#ifndef KIWIENGINE_RENDERER_H
#define KIWIENGINE_RENDERER_H

#include "../../Core/Graphics.h"
#include "../Scene/Level.h"
#include "../Primitives/FPSCamera.h"
#include "Program.h"

namespace Kiwi {
    namespace Engine {
        namespace Renderer {
            class Renderer {
            public:
                Renderer();

                void bindShaders(std::vector<GLProgram> shaders) { _shaders = shaders; };

                void bindLevel(Scene::Level level) { _level = level; };

                void bindCamera(Primitive::FPSCamera camera) { _camera = camera; };

                void render();

            private:
                Primitive::FPSCamera _camera;
                Scene::Level _level;
                std::vector<GLProgram> _shaders;

            };
        }
    }
}

#endif //KIWIENGINE_RENDERER_H
