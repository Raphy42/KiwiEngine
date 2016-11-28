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

                for (auto it : _level.getScene()->getChildren()) {
                    GLProgram program = _shaders[static_cast<int>(it.getMaterial().getType())];

                    glUseProgram(program.get());
                    glm::mat4 view;
                    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

                    glUniform4fv(glGetUniformLocation(program.get(), "view"), 1, glm::value_ptr(view));
                    glUniform4fv(glGetUniformLocation(program.get(), "model"), 1, glm::value_ptr(glm::mat4()));
                    glUniform4fv(glGetUniformLocation(program.get(), "perspective"), 1,
                                 glm::value_ptr(glm::perspective(67.f, 1200.f / 600.f, 0.1f, 100.f)));
                    it.getMesh().bind();
                    it.getMesh().draw();
                }
            }
        }
    }
}