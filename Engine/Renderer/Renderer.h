//
// Created by Raphaël Dantzer on 26/11/16.
//

#ifndef KIWIENGINE_RENDERER_H
#define KIWIENGINE_RENDERER_H

#include "../../Core/Graphics.h"
#include "../Scene/Level.h"
#include "../Primitives/FPSCamera.h"
#include "Program.h"
#include "Target.h"
#include "Shading.h"

namespace Kiwi {
    namespace Engine {
        namespace Renderer {
            class Renderer {
            public:
                Renderer();

                void bindTarget(Target target);

                void bindShaders(std::vector<GLProgram> shaders) { _shaders = shaders; };

                void bindShader(Shading::Type type, GLProgram shader);

                void bindLevel(Scene::Level level);

                void bindCamera(Primitive::FPSCamera *camera) { _camera = camera; };

                void render();

            private:
                void recursiveRender(Scene::Entity node);
                void renderNode(Scene::Entity node);

                std::vector<Material>       _materials;
                Primitive::FPSCamera        *_camera;
                Scene::Level                _level;
                std::vector<GLProgram>      _shaders;
                Target                      _target;

                glm::vec3 _lightpos = glm::vec3(0.f, 1.f, 0.f);
                glm::vec3 _lightcolor = glm::vec3(1.f, 1.f, 1.f);
                glm::vec3 _lightambient = glm::vec3(1.f, 0.9f, 0.9f);

                float _falloff = .12f;
                float _radius = 10.f;


                void updateNode(Scene::Entity node);

                bool _shadows = false;
            };
        }
    }
}

#endif //KIWIENGINE_RENDERER_H
