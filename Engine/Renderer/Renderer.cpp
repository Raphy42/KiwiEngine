//
// Created by Raphaël Dantzer on 28/11/16.
//

#include <iostream>
#include "Renderer.h"
#include "ShaderBuilder.h"
#include "../../Core/Config.h"
#include "../Assets/Loader.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

namespace Kiwi {
    namespace Engine {
        namespace Renderer {
            Renderer::Renderer() {
            }

            void Renderer::render() {
                //TODO dont leave this here !

                if (_materials.size() == 0) {
                    Asset::Loader loader;
                    _materials.push_back(
                            Material(loader.createTexture(Asset::Loader::Target::FLAT, "./Assets/textures/debug.png")));
                }
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glEnable(GL_DEPTH_TEST);
                for (auto node : _level.getScene()->getChildren()) {
                    renderNode(node);
                    for (auto it : node.getChildren()) {
                        renderNode(it);
                    }
                }
            }

            void Renderer::renderNode(Scene::Node node) {
                glm::vec3 lightPos(0.f, 3.f, 0.f);
                glm::vec3 camera = _camera->getPosition();
                GLProgram program = _shaders[static_cast<int>(node.getMaterial().getType())];

                glUseProgram(program.get());

                //todo refactor camera
                //todo refactor perspective
                //todo refactor uniforms

                glUniformMatrix4fv(glGetUniformLocation(program.get(), "view"),
                                   1, GL_FALSE, glm::value_ptr(_camera->getViewMat4()));
                glUniformMatrix4fv(glGetUniformLocation(program.get(), "model"),
                                   1, GL_FALSE, glm::value_ptr(node.getWorldPos()));
                glUniformMatrix4fv(glGetUniformLocation(program.get(), "projection"),
                                   1, GL_FALSE, glm::value_ptr(_camera->getProjectionMat4()));

                if (node.getMaterial().getType() == Material::Type::BASIC_LIGHTING)
                {
                    GLint lightPosLoc    = glGetUniformLocation(program.get(), "light.position");
                    GLint viewPosLoc     = glGetUniformLocation(program.get(), "viewPos");
                    glUniform3f(lightPosLoc,    lightPos.x, lightPos.y, lightPos.z);
                    glUniform3f(viewPosLoc,     camera.x, camera.y, camera.z);
                    // Set lights properties
                    glm::vec3 lightColor;
                    lightColor.x = sin(glfwGetTime() * 2.0f);
                    lightColor.y = sin(glfwGetTime() * 0.7f);
                    lightColor.z = sin(glfwGetTime() * 1.3f);
                    glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // Decrease the influence
                    glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // Low influence
                    glUniform3f(glGetUniformLocation(program.get(), "light.ambient"),  ambientColor.x, ambientColor.y, ambientColor.z);
                    glUniform3f(glGetUniformLocation(program.get(), "light.diffuse"),  diffuseColor.x, diffuseColor.y, diffuseColor.z);
                    glUniform3f(glGetUniformLocation(program.get(), "light.specular"), 1.0f, 1.0f, 1.0f);
                    // Set material properties
                    glUniform3f(glGetUniformLocation(program.get(), "material.ambient"),   1.0f, 0.5f, 0.31f);
                    glUniform3f(glGetUniformLocation(program.get(), "material.diffuse"),   1.0f, 0.5f, 0.31f);
                    glUniform3f(glGetUniformLocation(program.get(), "material.specular"),  0.5f, 0.5f, 0.5f); // Specular doesn't have full effect on this object's material
                    glUniform1f(glGetUniformLocation(program.get(), "material.shininess"), 32.0f);
                }

                glActiveTexture(GL_TEXTURE0);
//                node.getMaterial().bind();
                _materials[0].bind();
                glUniform1i(glGetUniformLocation(program.get(), "tex"), 0);
                node.getMesh().bind();
                node.getMesh().draw();
            }
        }
    }
}