//
// Created by Raphaël Dantzer on 26/11/16.
//

#ifndef KIWIENGINE_MESH_H
#define KIWIENGINE_MESH_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>
#include "../../Core/CoreGraphics.h"
#include "../Renderer/Texture.h"

namespace Kiwi {
    namespace Engine {
        namespace Primitive {
            struct Vertex {
                glm::vec3       position;
                glm::vec3       normal;
                glm::vec2       texture;
            };
            class Mesh {
            public:
                Mesh() {};
                Mesh(GLuint _vao, GLuint _vbo, GLuint _ebo) : _vao(_vao), _vbo(_vbo), _ebo(_ebo) {}

                virtual ~Mesh() {};

            protected:
                GLuint _vao;
                GLuint _vbo;
                GLuint _ebo;
            };
        }
    }
}

#endif //KIWIENGINE_MESH_H
