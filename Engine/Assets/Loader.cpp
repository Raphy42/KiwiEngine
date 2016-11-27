//
// Created by Raphael DANTZER on 11/27/16.
//

#include "Loader.h"

namespace kE = Kiwi::Engine;

kE::Primitive::Mesh *
kE::Asset::Loader::createMeshFromAttributes(kE::Asset::Loader::Vertices v,
                                            kE::Asset::Loader::Indices i,
                                            kE::Asset::Loader::Textures t)
{
    GLuint      vao, vbo, ebo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(kE::Primitive::Vertex) * v.size() , &v[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * v.size(), &i[0], GL_STATIC_DRAW);


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(kE::Primitive::Vertex), nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(kE::Primitive::Vertex), (GLvoid *)offsetof(kE::Primitive::Vertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(kE::Primitive::Vertex), (GLvoid *)offsetof(kE::Primitive::Vertex, texture));

    glBindVertexArray(0);
}
