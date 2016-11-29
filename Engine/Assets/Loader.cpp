//
// Created by Raphael DANTZER on 11/27/16.
//

#include <string>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include "Loader.h"
#include "../../Core/Config.h"

namespace kE = Kiwi::Engine;

kE::Primitive::Mesh
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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * i.size(), &i[0], GL_STATIC_DRAW);


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(kE::Primitive::Vertex), nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(kE::Primitive::Vertex), (GLvoid *)offsetof(kE::Primitive::Vertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(kE::Primitive::Vertex), (GLvoid *)offsetof(kE::Primitive::Vertex, texture));

    glBindVertexArray(0);

    kE::Primitive::Mesh mesh(vao, vbo, ebo, i.size());
    return mesh;
}

kE::Primitive::Mesh
Kiwi::Engine::Asset::Loader::createMeshFromVertices(std::vector<float> v) {
    GLuint vao, vbo, ebo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    ebo = 0U;

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * v.size(), &v[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);

    glBindVertexArray(0);

    return kE::Primitive::Mesh(vao, vbo, ebo, v.size() / 3);
}
//
//kE::Primitive::Model
//Kiwi::Engine::Asset::Loader::createModel(std::string source) {
//    const aiScene *scene = _importer.ReadFileFromMemory(source.c_str(), source.size(), aiProcess_Triangulate | aiProcess_FlipUVs);
//
//    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
//        return nullptr;
//    kE::Primitive::Model *model = new kE::Primitive::Model();
//
//}
//
//void
//Kiwi::Engine::Asset::Loader::processNode(kE::Primitive::Model *model, aiNode *node, const aiScene *scene) {
//    for(GLuint i = 0; i < node->mNumMeshes; i++)
//    {
//        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
//        model->_meshes.push_back(this->processMesh(mesh, scene));
//    }
//    for(GLuint i = 0; i < node->mNumChildren; i++)
//    {
//        processNode(model, node->mChildren[i], scene);
//    }
//}
//
//kE::Primitive::Mesh
//kE::Asset::Loader::processMesh(aiMesh *mesh, const aiScene *scene) {
//    Vertices        vertices;
//    Indices         indices;
//    Textures        textures;
//
//    for (GLuint i = 0; i < mesh->mNumVertices; ++i)
//    {
//        kE::Primitive::Vertex   vertex;
//
//        vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
//        vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
//        if (mesh->mTextureCoords[0])
//            vertex.texture = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
//        else
//            vertex.texture = glm::vec2(0.f, 0.f);
//        vertices.push_back(vertex);
//    }
//
//    for (GLuint i = 0; i < mesh->mNumFaces; ++i)
//    {
//        aiFace face = mesh->mFaces[i];
//        for (GLuint j = 0; j < face.mNumIndices; ++j)
//            indices.push_back(face.mIndices[j]);
//    }
//    if (mesh->mMaterialIndex >= 0)
//    {
//        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
//
//        Textures diffuseMaps = processTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
//        textures.emplace_back(diffuseMaps);
//
//        Textures specularMaps = processTextures(material, aiTextureType_SPECULAR, "texture_specular");
//        textures.emplace_back(specularMaps);
//    }
//
//}
//
//kE::Renderer::Texture
//kE::Asset::Loader::processTexture(aiMaterial *material, aiTextureType type, std::string name) {
//    return Kiwi::Engine::Renderer::Texture();
//}
//
//kE::Asset::Loader::Textures
//kE::Asset::Loader::processTextures(aiMaterial *material, aiTextureType type, std::string name) {
//    Textures textures;
//
//    for(GLuint i = 0; i < material->GetTextureCount(type); i++)
//    {
//        aiString str;
//        material->GetTexture(type, i, &str);
//        kE::Renderer::Texture texture;
//        texture.id = TextureFromFile(str.C_Str(), this->directory);
//        texture.type = name;
//        texture.path = str;
//        textures.push_back(texture);
//    }
//    return textures;
//}
