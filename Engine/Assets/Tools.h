//
// Created by Raphaël Dantzer on 30/11/16.
//

#ifndef KIWIENGINE_TOOLS_H
#define KIWIENGINE_TOOLS_H

#include <vector>
#include <glm/common.hpp>
#include "../../Core/Graphics.h"

namespace Kiwi {
    namespace Engine {
        namespace Asset {
            template<typename out = float,
                    typename V = glm::vec3,
                    typename UV = glm::vec2,
                    typename N = glm::vec3>

            /**
             * Generates an interleaved vector of float for GPU upload
             * @param vertices
             * @param uv
             * @param normals
             * @return
             */
            inline std::vector<out>
            generate_interleave_buffer_vuvn(std::vector<V> vertices,
                                       std::vector<UV> uv = std::vector<UV>(),
                                       std::vector<N> normals = std::vector<N>()) {
                std::vector<out> interleaved_data;

                interleaved_data.reserve(vertices.size() + uv.size() + normals.size());

                for (int i = 0; i < vertices.size(); ++i) {
                    interleaved_data.push_back(vertices[i].x);
                    interleaved_data.push_back(vertices[i].y);
                    interleaved_data.push_back(vertices[i].z);
                    if (uv.size()) {
                        interleaved_data.push_back(uv[i].x);
                        interleaved_data.push_back(uv[i].y);
                    }
                    if (normals.size()) {
                        interleaved_data.push_back(normals[i].x);
                        interleaved_data.push_back(normals[i].y);
                        interleaved_data.push_back(normals[i].z);
                    }
                }
                return interleaved_data;
            }

            template<typename out = float,
                    typename V = glm::vec3,
                    typename UV = glm::vec2,
                    typename N = glm::vec3,
                    typename Bi = glm::vec3,
                    typename T = glm::vec3>

            /**
             * Generates an interleaved vector of float for GPU upload
             * @param vertices
             * @param uv
             * @param normals
             * @param bi-tangent
             * @param tangent
             * @return
             */
            inline std::vector<out>
            generate_interleave_buffer_vuvnbit(std::vector<V> vertices,
                                       std::vector<UV> uv = std::vector<UV>(),
                                       std::vector<N> n = std::vector<N>(),
                                       std::vector<Bi> b = std::vector<Bi>(),
                                       std::vector<T> t = std::vector<T>()) {
                std::vector<out> interleaved_data;

                interleaved_data.reserve(vertices.size() + uv.size() + n.size() + b.size() + t.size());

                for (int i = 0; i < vertices.size(); ++i) {
                    interleaved_data.push_back(vertices[i].x);
                    interleaved_data.push_back(vertices[i].y);
                    interleaved_data.push_back(vertices[i].z);
                    if (uv.size()) {
                        interleaved_data.push_back(uv[i].x);
                        interleaved_data.push_back(uv[i].y);
                    }
                    if (n.size()) {
                        interleaved_data.push_back(n[i].x);
                        interleaved_data.push_back(n[i].y);
                        interleaved_data.push_back(n[i].z);
                    }
                    if (b.size()) {
                        interleaved_data.push_back(b[i].x);
                        interleaved_data.push_back(b[i].y);
                        interleaved_data.push_back(b[i].z);
                    }
                    if (t.size()) {
                        interleaved_data.push_back(t[i].x);
                        interleaved_data.push_back(t[i].y);
                        interleaved_data.push_back(t[i].z);
                    }
                }
                return interleaved_data;
            }

            template<typename V = glm::vec3,
                    typename UV = glm::vec2,
                    typename N = glm::vec3,
                    typename Bi = glm::vec3,
                    typename T = glm::vec3>

            /**
             * operate gl state machine accordingly and creates all the VertexAttribPointer
             * @param vertices
             * @param uv
             * @param normals
             * @param bi-tangent
             * @param tangent
             */

            inline void generate_vertex_attrib_array(std::vector<V> v,
                                                     std::vector<UV> uv = std::vector<UV>(),
                                                     std::vector<N> n = std::vector<N>(),
                                                     std::vector<Bi> b = std::vector<Bi>(),
                                                     std::vector<T> t = std::vector<T>())
            {
                std::size_t stride = sizeof(V);
                if (uv.size() > 0)
                    stride += sizeof(UV);
                if (n.size() > 0)
                    stride += sizeof(N);
                if (b.size() > 0)
                    stride += sizeof(Bi);
                if (t.size() > 0)
                    stride += sizeof(T);

                std::size_t offset = 0;

                glEnableVertexAttribArray(0);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid *) offset);

                offset += sizeof(V);

                if (uv.size() > 0) {
                    glEnableVertexAttribArray(1);
                    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid *) offset);
                    offset += sizeof(UV);
                }
                if (n.size() > 0) {
                    glEnableVertexAttribArray(2);
                    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid *) offset);
                    offset += sizeof(N);
                }
                if (b.size() > 0) {
                    glEnableVertexAttribArray(3);
                    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid *) offset);
                    offset += sizeof(Bi);
                }
                if (t.size() > 0) {
                    glEnableVertexAttribArray(4);
                    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid *) offset);
                    offset += sizeof(T);
                }
            }

        }
    }
}

#endif //KIWIENGINE_TOOLS_H
