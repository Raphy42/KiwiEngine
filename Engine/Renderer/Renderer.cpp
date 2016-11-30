//
// Created by Raphaël Dantzer on 28/11/16.
//

#include <iostream>
#include "Renderer.h"
#include "ShaderBuilder.h"
#include "../../Core/Config.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

namespace Kiwi {
    namespace Engine {
        namespace Renderer {
            Renderer::Renderer() {}

            void Renderer::render() {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glEnable(GL_DEPTH_TEST);
                for (auto it : _level.getScene()->getChildren()) {
                    GLProgram program = _shaders[static_cast<int>(it.getMaterial().getType())];

                    glUseProgram(program.get());

                    //todo refactor camera
                    //todo refactor perspective
                    //todo refactor uniforms

                    glUniformMatrix4fv(glGetUniformLocation(program.get(), "view"),
                                       1, GL_FALSE, glm::value_ptr(_camera->getViewMat4()));
                    glUniformMatrix4fv(glGetUniformLocation(program.get(), "model"),
                                       1, GL_FALSE, glm::value_ptr(it.getWorldPos()));
                    glUniformMatrix4fv(glGetUniformLocation(program.get(), "projection"),
                                       1, GL_FALSE, glm::value_ptr(_camera->getProjectionMat4()));

                    glActiveTexture(GL_TEXTURE0);
                    it.getMaterial().bind();
                    glUniform1i(glGetUniformLocation(program.get(), "tex"), 0);
                    it.getMesh().bind();
                    it.getMesh().draw();
                }
            }
        }
    }
}