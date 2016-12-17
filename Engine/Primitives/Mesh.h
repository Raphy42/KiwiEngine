//
// Created by Raphaël Dantzer on 26/11/16.
//

#ifndef KIWIENGINE_MESH_H
#define KIWIENGINE_MESH_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>
#include <glm/detail/type_mat.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/string.hpp>
#include "../../Core/Graphics.h"

namespace Kiwi {
    namespace Engine {
        namespace Primitive {
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

                Mesh() = default;

                Mesh(GLuint vao, GLuint vbo, GLuint ebo, unsigned long size) :
                        _vao(vao),
                        _vbo(vbo),
                        _ebo(ebo),
                        _size(size),
                        _topology(Topology::TRIANGLES)
                {}

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
                    glBindVertexArray(0);

                }



                virtual ~Mesh() {};

            protected:
                GLuint          _vao;
                GLuint          _vbo;
                GLuint          _ebo;
                unsigned long   _size;

            private:
                friend class boost::serialization::access;

                template <class Archive>
                void serialize(Archive &ar, const unsigned int flags) {
                    ar & BOOST_SERIALIZATION_NVP(_vao);
                    ar & BOOST_SERIALIZATION_NVP(_vbo);
                    ar & BOOST_SERIALIZATION_NVP(_ebo);
                    ar & BOOST_SERIALIZATION_NVP(_size);
                    ar & BOOST_SERIALIZATION_NVP(_topology);
                }

                Topology _topology;
            };
        }
    }
}

#endif //KIWIENGINE_MESH_H
