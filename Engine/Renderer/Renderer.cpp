//
// Created by Raphaël Dantzer on 28/11/16.
//

#include <iostream>
#include "Renderer.h"
#include "ShaderBuilder.h"
#include "../../Core/Config.h"
#include "../Assets/Loader.h"
#include "Shading.h"
#include "../../vendor/imgui/imgui.h"
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
                _target.bindFrame();

                glClearColor(0.1f, 0.1f, 0.1f, 1.f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                glEnable(GL_DEPTH_TEST);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glDepthFunc(GL_LESS);

                recursiveRender(_level.get_root());

                glUseProgram(0);
                glBindVertexArray(0);

                glDepthFunc(GL_LEQUAL);

                GLProgram p = _shaders[static_cast<int>(_level.getSkybox().getMaterial()->getType())];
                glUseProgram(p.get());

                renderNode(_level.getSkybox());

//                _target.renderFrame(static_cast<int>(Shading::Type::POST_PROCESS));
            }

            void Renderer::renderNode(Scene::Entity node) {
                glm::vec3 lightPos = glm::vec3(1.f, 1.f, 1.f);
                glm::vec3 camera = _camera->getPosition();
                GLProgram program = _shaders[static_cast<int>(node.getMaterial()->getType())];

                //todo refactor camera
                //todo refactor perspective
                //todo refactor uniforms

                glUseProgram(program.get());

                glUniformMatrix4fv(glGetUniformLocation(program.get(), "view"),
                                   1, GL_FALSE, glm::value_ptr(_camera->getViewMat4()));
                glUniformMatrix4fv(glGetUniformLocation(program.get(), "model"),
                                   1, GL_FALSE, glm::value_ptr(node.getWorldPos()));
                glUniformMatrix4fv(glGetUniformLocation(program.get(), "projection"),
                                   1, GL_FALSE, glm::value_ptr(_camera->getProjectionMat4()));

                if (node.getMaterial()->getType() == Shading::Type::PHONG) {
                    node.getMaterial()->setVec3Parameter("light_pos", glm::vec3(0.f, 3.f, 0.f));
                    node.getMaterial()->setVec3Parameter("view_pos", camera);
                    node.getMaterial()->setVec3Parameter("light_color", glm::vec3(1.0f, 1.0f, 1.0f));
                } else if (node.getMaterial()->getType() == Shading::Type::PHONG_TEXTURED) {
                    node.getMaterial()->setVec3Parameter("light_position", glm::vec3(0.f, 5.f, 0.f));
                    node.getMaterial()->setVec3Parameter("light_color", glm::vec3(1.f, 1.f, 1.f));
                    node.getMaterial()->setVec3Parameter("light_ambient", glm::vec3(0.8f, 0.7f, 0.69f));
                    node.getMaterial()->setParameter("light_falloff", .12f);
                    node.getMaterial()->setParameter("light_radius", 10.f);
                }

                node.getMaterial()->bind(0);
                node.getMesh().bind();
                node.getMesh().draw();
                glBindTexture(GL_TEXTURE_2D, 0);
            }


            void Renderer::recursiveRender(Scene::Entity node) {
                if (node.getMaterial() == nullptr)
                    for (auto &entity : node.getChildren())
                        recursiveRender(entity);
                else
                    renderNode(node);
            }

            void Renderer::bindTarget(Target target) {
                _target = target;
            }

            void Renderer::bindShader(Shading::Type type, GLProgram shader) {
                _shaders[static_cast<int>(type)] = shader;
            }

            void Renderer::updateNode(Scene::Entity node) {
                if (!node.getMaterial()) {
                    for (auto &entity : node.getChildren()) {
                        updateNode(entity);
                        entity.getMaterial()->bindShader(_shaders[static_cast<int>(entity.getMaterial()->getType())]);
                    }
                }
            }

            void Renderer::bindLevel(Scene::Level level) {
                _level = level;
                for (auto entity : _level.get_root().getChildren()) {
                    if (entity.getMaterial())
                        entity.getMaterial()->bindShader(_shaders[static_cast<int>(entity.getMaterial()->getType())]);
                }
                _level.getSkybox().getMaterial()->bindShader(_shaders[static_cast<int>(Shading::Type::SKYBOX)]);
            }
        }
    }
}