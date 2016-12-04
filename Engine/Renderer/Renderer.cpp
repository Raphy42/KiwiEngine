//
// Created by Raphaël Dantzer on 28/11/16.
//

#include <iostream>
#include "Renderer.h"
#include "ShaderBuilder.h"
#include "../../Core/Config.h"
#include "../Assets/Loader.h"
#include "Shading.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

namespace Kiwi {
    namespace Engine {
        namespace Renderer {

            Renderer::Renderer() {
                _shaders.reserve(static_cast<int>(Shading::Type::DEBUG));
                for (int i = 0; i < static_cast<int>(Shading::Type::DEBUG); ++i) {
                    _shaders.push_back(GLProgram());
                }
            }

            void Renderer::render() {
//                _target.bindFrame();

                glClearColor(0.1f, 0.1f, 0.1f, 1.f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glEnable(GL_DEPTH_TEST);
                for (auto node : _level.getScene()->getChildren()) {
                    renderNode(node);
                    for (auto it : node.getChildren()) {
                        renderNode(it);
                    }
                }

//                glUseProgram(0);
//                _target.renderFrame(_shaders[2]);
            }

            void Renderer::renderNode(Scene::Entity node) {
                glm::vec3 lightPos = glm::vec3(1.f, 1.f, 1.f);
                glm::vec3 camera = _camera->getPosition();
                GLProgram program = _shaders[static_cast<int>(node.getMaterial()->getType())];

                //todo refactor camera
                //todo refactor perspective
                //todo refactor uniforms

                glUniformMatrix4fv(glGetUniformLocation(program.get(), "view"),
                                   1, GL_FALSE, glm::value_ptr(_camera->getViewMat4()));
                glUniformMatrix4fv(glGetUniformLocation(program.get(), "model"),
                                   1, GL_FALSE, glm::value_ptr(node.getWorldPos()));
                glUniformMatrix4fv(glGetUniformLocation(program.get(), "projection"),
                                   1, GL_FALSE, glm::value_ptr(_camera->getProjectionMat4()));

                node.getMaterial()->setParameter("light_pos", glm::vec3(0.f, 1.f, 0.f));
                node.getMaterial()->setParameter("view_pos", camera);
                node.getMaterial()->setParameter("light_color", glm::vec3(1.0f, 1.0f, 1.0f));

                node.getMaterial()->bindTextures(0);
                node.getMesh().bind();
                node.getMesh().draw();
                glBindTexture(GL_TEXTURE_2D, 0);
            }

            void Renderer::bindTarget(Target target) {
                _target = target;
            }

            void Renderer::bindShader(Shading::Type type, GLProgram shader) {
                _shaders[static_cast<int>(type)] = shader;
            }

            void Renderer::bindLevel(Scene::Level level) {
                _level = level;
                for (auto entity : _level.get_root()->getChildren())
                    entity.getMaterial()->bindShader(_shaders[static_cast<int>(entity.getMaterial()->getType())]);
            }
        }
    }
}