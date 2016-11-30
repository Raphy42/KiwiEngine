//
// Created by Raphael DANTZER on 11/27/16.
//

#include <string>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include "Loader.h"
#include "../../Core/Config.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

kE::Primitive::Mesh Kiwi::Engine::Asset::Loader::createDefaultMesh(Kiwi::Engine::Asset::Loader::Type type) {
    std::vector<float> vertices = {
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f
    };

    std::vector<float> uv = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 1.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 1.0f,
    };

    std::vector<float> normals = {
            0.0f,  0.0f, -1.0f,
            0.0f,  0.0f, -1.0f,
            0.0f,  0.0f, -1.0f,
            0.0f,  0.0f, -1.0f,
            0.0f,  0.0f, -1.0f,
            0.0f,  0.0f, -1.0f,

            0.0f,  0.0f,  1.0f,
            0.0f,  0.0f,  1.0f,
            0.0f,  0.0f,  1.0f,
            0.0f,  0.0f,  1.0f,
            0.0f,  0.0f,  1.0f,
            0.0f,  0.0f,  1.0f,

            1.0f,  0.0f,  0.0f,
            1.0f,  0.0f,  0.0f,
            1.0f,  0.0f,  0.0f,
            1.0f,  0.0f,  0.0f,
            1.0f,  0.0f,  0.0f,
            1.0f,  0.0f,  0.0f,

            1.0f,  0.0f,  0.0f,
            1.0f,  0.0f,  0.0f,
            1.0f,  0.0f,  0.0f,
            1.0f,  0.0f,  0.0f,
            1.0f,  0.0f,  0.0f,
            1.0f,  0.0f,  0.0f,

            0.0f, -1.0f,  0.0f,
            0.0f, -1.0f,  0.0f,
            0.0f, -1.0f,  0.0f,
            0.0f, -1.0f,  0.0f,
            0.0f, -1.0f,  0.0f,
            0.0f, -1.0f,  0.0f,

            0.0f,  1.0f,  0.0f,
            0.0f,  1.0f,  0.0f,
            0.0f,  1.0f,  0.0f,
            0.0f,  1.0f,  0.0f,
            0.0f,  1.0f,  0.0f,
            0.0f,  1.0f,  0.0f,
    };
    switch (type) {
        case Type::CUBE :
            return createMeshVUVNStride(vertices, uv, normals);
            break;
        case Type::PLANE :
            return kE::Primitive::Mesh();
            break;
    }
}

/*
 * Todo: Template all of this
 */

kE::Primitive::Mesh
Kiwi::Engine::Asset::Loader::createMeshVUVNStride(std::vector<float> v, std::vector<float> uv, std::vector<float> n) {
    GLuint      vao, vbo, ebo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
//    glGenBuffers(1, &ebo);

    std::vector<float>      interleaved_data;

    for (int i = 0; i < v.size();) {
        interleaved_data.push_back(v[i]);
        interleaved_data.push_back(v[i + 1]);
        interleaved_data.push_back(v[i + 2]);

        if (uv.size())
        {
            interleaved_data.push_back(n[i]);
            interleaved_data.push_back(n[i + 1]);
        }
        if (n.size())
        {
            interleaved_data.push_back(n[i]);
            interleaved_data.push_back(n[i + 1]);
            interleaved_data.push_back(n[i + 2]);
        }
        i += 3;
    }

    interleaved_data.insert(interleaved_data.end(), uv.begin(), uv.end());
    interleaved_data.insert(interleaved_data.end(), n.begin(), n.end());


    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, interleaved_data.size() * sizeof(float) , &interleaved_data[0], GL_STATIC_DRAW);


    std::size_t stride = 3 * sizeof(float);
    if (uv.size() > 0)
        stride += 2 * sizeof(float);
    if (n.size() > 0)
        stride += 3 * sizeof(float);

    std::size_t offset = 0;

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid *)offset);

    offset += 3 * sizeof(float);

    if (uv.size() > 0) {
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid *)offset);
        offset += 2 * sizeof(float);
    }
    if (n.size() > 0) {
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid *)offset);
        offset += 3 * sizeof(float);
    }

    glBindVertexArray(0);

    kE::Primitive::Mesh mesh(vao, vbo, 0U, v.size() / 3);
    return mesh;
}

kE::Renderer::Texture
Kiwi::Engine::Asset::Loader::createTexture(Kiwi::Engine::Asset::Loader::Target target, std::string source) {
    int w, h, comp;
    const unsigned char *image = stbi_load(source.c_str(), &w, &h, &comp, STBI_rgb);

    if (!image)
        throw std::runtime_error("TG");
    GLuint texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    return kE::Renderer::Texture(GL_TEXTURE_2D, texture);
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
