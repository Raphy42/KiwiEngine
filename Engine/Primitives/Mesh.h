//
// Created by Raphaël Dantzer on 26/11/16.
//

#ifndef KIWIENGINE_MESH_H
#define KIWIENGINE_MESH_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>
#include <glm/detail/type_mat.hpp>
#include "../../Core/Graphics.h"

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
                enum class Topology : GLenum {
                    POINTS = GL_POINTS,
                    LINES = GL_LINES,
                    LINE_STRIP = GL_LINE_STRIP,
                    TRIANGLES = GL_TRIANGLES,
                    TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
                    TRIANGLE_FAN = GL_TRIANGLE_FAN
                };

                Mesh() {};

                Mesh(GLuint vao, GLuint vbo, GLuint ebo, unsigned long size) :
                        _vao(vao),
                        _vbo(vbo),
                        _ebo(ebo),
                        _topology(Topology::TRIANGLES),
                        _size(size) {}

                void bind(void) const {
                    glBindVertexArray(_vao);
                }

                void setTopology(Topology topology) {
                    _topology = topology;
                }

                void draw(void) const {
                    if (_ebo)
                        glDrawElements((GLenum) _topology, _size, GL_UNSIGNED_INT, 0);
                    else
                        glDrawArrays((GLenum) _topology, 0, (GLsizei) _size);

                }



                virtual ~Mesh() {};

            protected:
                GLuint          _vao;
                GLuint          _vbo;
                GLuint          _ebo;
                unsigned long   _size;

            private:
                Topology _topology;
            };
        }
    }
}

#endif //KIWIENGINE_MESH_H
