//
// Created by Raphael DANTZER on 12/14/16.
//

#ifndef KIWIENGINE_SHADOWMAP_H
#define KIWIENGINE_SHADOWMAP_H

#include <glm/vec3.hpp>
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include <vector>
#include "../../Core/Graphics.h"
#include "Program.h"

namespace Kiwi {
    namespace Engine {
        namespace Renderer {
            class ShadowMap {
            public:
                ShadowMap() = default;
                ShadowMap(float width, int height);
                ~ShadowMap() = default;

                void    update(glm::vec3 lightPosition);
                void    bind(GLProgram shader);

            private:
                glm::mat4               _shadowProjection;
                std::vector<glm::mat4>  _shadowTransforms;

                float                   _width;
                float                   _height;

                GLuint                  _fbo;
                GLProgram               _shader;
                float                   _near = 1.f;
                float                   _far = 25.f;

                glm::vec3               _lightPos;

            };

        }
    }
}

#endif //KIWIENGINE_SHADOWMAP_H
