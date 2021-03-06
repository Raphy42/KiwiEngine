//
// Created by Raphael DANTZER on 11/27/16.
//

#include <string>
#include "Loader.h"
#include "../../Core/Config.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
#include "Tools.h"
#include "ugly.h"
#include "../Renderer/PhongTexturedMaterial.h"
#include "../Renderer/PhongMaterial.h"
#include "../Renderer/Target.h"


extern struct _cube cube;

namespace kE = Kiwi::Engine;

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

kE::Primitive::Mesh
Kiwi::Engine::Asset::Loader::createDefaultMesh(Kiwi::Engine::Asset::Loader::Type type) {
    switch (type) {
        case Type::CUBE :
            return createMeshVUVNStride(cube.v, cube.uv, cube.n);
        case Type::PLANE :
            return createPlane(10, 10);
        default:
            break;
    }
}

/*
 * Todo: Template all of this
 */

kE::Primitive::Mesh
Kiwi::Engine::Asset::Loader::createMeshVUVNStride(std::vector<glm::vec3> v, std::vector<glm::vec2> uv,
                                                  std::vector<glm::vec3> n) {
    GLuint vao, vbo, ebo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
//    glGenBuffers(1, &ebo);

    std::vector<float> interleaved_data = generate_interleave_buffer_vuvn(v, uv, n);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, interleaved_data.size() * sizeof(float), &interleaved_data[0], GL_STATIC_DRAW);

    generate_vertex_attrib_array(v, uv, n);

    glBindVertexArray(0);

    kE::Primitive::Mesh mesh(vao, vbo, 0U, v.size());
    return mesh;
}

kE::Renderer::Texture
Kiwi::Engine::Asset::Loader::createTexture(Kiwi::Engine::Asset::Loader::Target target, std::string source) {
    int w, h, comp;
    stbi_set_flip_vertically_on_load(true);

    unsigned char *image = stbi_load(source.c_str(), &w, &h, &comp, STBI_default);

    if (image == nullptr)
        throw std::runtime_error(std::string(stbi_failure_reason()) + " : " + source);

    GLenum format;
    if (comp == 1)
        format = GL_RED;
    else if (comp == 3)
        format = GL_RGB;
    else if (comp == 4 || comp == 2)
        format = GL_RGBA;
    else
        throw std::invalid_argument("Texture has invalid format: " + source);
    std::cout << "Loading source " + source << std::endl;

    GLuint texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(image);
    return kE::Renderer::Texture(GL_TEXTURE_2D, texture);
}

Kiwi::Engine::Primitive::Mesh
Kiwi::Engine::Asset::Loader::createPlane(unsigned int rows, unsigned int columns) {
    bool oddRow = false;

    float dX = 1.0f / rows;
    float dY = 1.0f / columns;

    std::vector<glm::vec3> v;
    std::vector<glm::vec2> uv;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indices;

    for (int y = 0; y <= columns; ++y) {
        for (int x = 0; x <= rows; ++x) {
            v.push_back(glm::vec3(dX * x * 2.0f - 1.0f, dY * y * 2.0f - 1.0f, 0.0f));
            uv.push_back(glm::vec2(dX * x, 1.0f - y * dY));
            normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
        }
    }

    for (int y = 0; y < columns; ++y) {
        if (!oddRow) {
            for (int x = 0; x <= rows; ++x) {
                indices.push_back(y * (rows + 1) + x);
                indices.push_back((y + 1) * (rows + 1) + x);
            }
        } else {
            for (int x = rows; x >= 0; --x) {
                indices.push_back((y + 1) * (rows + 1) + x);
                indices.push_back(y * (rows + 1) + x);
            }
        }
        oddRow = !oddRow;
    }
    kE::Primitive::Mesh mesh = createMeshVUVNStrideIndexed(v, uv, normals, indices);
    mesh.setTopology(kE::Primitive::Mesh::Topology::TRIANGLE_STRIP);
    return mesh;
}

Kiwi::Engine::Primitive::Mesh
Kiwi::Engine::Asset::Loader::createMeshVUVNStrideIndexed(std::vector<glm::vec3> v, std::vector<glm::vec2> uv,
                                                         std::vector<glm::vec3> n, std::vector<unsigned int> i) {
    GLuint vao, vbo, ebo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    std::vector<float> interleaved_data = generate_interleave_buffer_vuvn(v, uv, n);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, interleaved_data.size() * sizeof(float), &interleaved_data[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, i.size() * sizeof(unsigned int), &i[0], GL_STATIC_DRAW);

    generate_vertex_attrib_array(v, uv, n);

    glBindVertexArray(0);

    kE::Primitive::Mesh mesh(vao, vbo, ebo, i.size());
    return mesh;
}

Kiwi::Engine::Primitive::Mesh
Kiwi::Engine::Asset::Loader::createMeshFromSimpleModel(const char *filename) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(filename, aiProcess_Triangulate |
                                                       aiProcess_GenNormals | aiProcess_FlipUVs |
                                                       aiProcess_JoinIdenticalVertices | aiProcess_GenUVCoords);

    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        throw std::runtime_error(importer.GetErrorString());
    aiMesh *mesh = scene->mMeshes[0];

    return processAiMesh(mesh, scene);
}

Kiwi::Engine::Primitive::Mesh
Kiwi::Engine::Asset::Loader::processAiMesh(aiMesh *mesh, const aiScene *aScene) {
    std::vector<glm::vec3> v, n, b, t;
    std::vector<glm::vec2> uvs;
    std::vector<unsigned int> idx;
    for (GLuint i = 0; i < mesh->mNumVertices; i++) {
        glm::vec3 vertex; // We declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // Positions
        vertex.x = mesh->mVertices[i].x;
        vertex.y = mesh->mVertices[i].y;
        vertex.z = mesh->mVertices[i].z;
        // Normals
        glm::vec3 normal;
        if (!mesh->HasNormals())
        {
            normal = glm::vec3(1.f);
        }
        else
        {
            normal.x = mesh->mNormals[i].x;
            normal.y = mesh->mNormals[i].y;
            normal.z = mesh->mNormals[i].z;
        }
        glm::vec2 uv;
        if (mesh->HasTextureCoords(0)) // Does the mesh contain texture coordinates?
        {
            // A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            uv.x = mesh->mTextureCoords[0][i].x;
            uv.y = mesh->mTextureCoords[0][i].y;
        } else {
            uv = glm::vec2(0.0f, 0.0f);
        }
        if (mesh->HasTangentsAndBitangents()) {
            glm::vec3 tangent(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z);
            glm::vec3 bitangent(mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z);
            t.push_back(tangent);
            b.push_back(bitangent);
        }
        //todo stream interleave
        v.push_back(vertex);
        n.push_back(normal);
        uvs.push_back(uv);
    }
    // Now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (GLuint i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        // Retrieve all indices of the face and store them in the indices vector
        for (GLuint j = 0; j < face.mNumIndices; j++)
            idx.push_back(face.mIndices[j]);
    }
    if (t.size() && b.size())
        return createMeshVUVNTBStrideIndexed(v, uvs, n, idx, b, t);
    else
        return createMeshVUVNStrideIndexed(v, uvs, n, idx);
}

Kiwi::Engine::Scene::Entity
Kiwi::Engine::Asset::Loader::createEntityFromModel(const char *filename) {
    std::string file = filename;
    _path = file.substr(0, file.find_last_of('/')); //todo potential fatal failure to fix
    kE::Scene::Entity node;
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(filename, aiProcess_Triangulate |
                                                       aiProcess_GenNormals |
                                                       aiProcess_JoinIdenticalVertices |
                                                       aiProcess_GenUVCoords | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        throw std::runtime_error(importer.GetErrorString());
    for (int i = 0; i < scene->mNumMeshes; ++i) {
        if (scene->mMeshes[i]->mMaterialIndex > 0) {
            aiString matName;
            scene->mMaterials[scene->mMeshes[i]->mMaterialIndex]->Get(AI_MATKEY_NAME, matName);

            std::cout << std::endl;
            std::cout << "Creating new PhongTexturedMaterial: " << matName.C_Str() << std::endl;

            kE::Renderer::PhongTexturedMaterial *material = new kE::Renderer::PhongTexturedMaterial();
            aiMaterial *obj_material = scene->mMaterials[scene->mMeshes[i]->mMaterialIndex];

            material->addMap(
                    loadMaterialTexture(obj_material, aiTextureType_DIFFUSE, kE::Renderer::Texture::Type::DIFFUSE));
            material->addMap(
                    loadMaterialTexture(obj_material, aiTextureType_HEIGHT, kE::Renderer::Texture::Type::NORMAL));
            material->addMap(
                    loadMaterialTexture(obj_material, aiTextureType_SPECULAR, kE::Renderer::Texture::Type::SPECULAR));
            material->addMap(
                    loadMaterialTexture(obj_material, aiTextureType_OPACITY, kE::Renderer::Texture::Type::ALPHA));
            kE::Primitive::Mesh mesh = processAiMesh(scene->mMeshes[i], scene);
            node.addChild(kE::Scene::Entity(mesh, material));
        } else { //no textures found, phongmaterial with white default color TODO: replace by debug
            kE::Renderer::PhongMaterial *material = new kE::Renderer::PhongMaterial();

            std::cout << "Phong material creation" << std::endl;

            material->setColor(glm::vec3(1.0f, 1.0f, 1.0f));
            kE::Primitive::Mesh mesh = processAiMesh(scene->mMeshes[i], scene);
            node.addChild(kE::Scene::Entity(mesh, material));
        }
    }
    return node;
}

kE::Renderer::Texture
Kiwi::Engine::Asset::Loader::loadMaterialTexture(aiMaterial *material, aiTextureType type,
                                                 kE::Renderer::Texture::Type map) {
    aiString str;
    if (!material->GetTextureCount(type)) {
        if (map == kE::Renderer::Texture::Type::DIFFUSE) {
            std::cout << "default diffuse" << std::endl;
            return _textureCache["diffuse"];
        }
        else if (map == kE::Renderer::Texture::Type::NORMAL) {
            std::cout << "default normal" << std::endl;
            return _textureCache["normal"];
        }
        else if (map == kE::Renderer::Texture::Type::SPECULAR) {
            std::cout << "default specular" << std::endl;
            return _textureCache["specular"];
        }
        else if (map == kE::Renderer::Texture::Type::ALPHA) {
            std::cout << "default alpha" << std::endl;
            return _textureCache["alpha"];
        }
    } else
        material->GetTexture(type, 0, &str);
    std::cout << str.C_Str() << std::endl;
    auto r = _textureCache.find(str.C_Str());
    if (r != _textureCache.end())
        return (_textureCache[str.C_Str()]);
    else {
        kE::Renderer::Texture texture = createMap(_path + '/' + str.C_Str(), map, map == kE::Renderer::Texture::Type::ALPHA);
        _textureCache[str.C_Str()] = texture;
        return (texture);
    }
}

Kiwi::Engine::Primitive::Mesh
Kiwi::Engine::Asset::Loader::createMeshVUVNTBStrideIndexed(std::vector<glm::vec3> v, std::vector<glm::vec2> uv,
                                                           std::vector<glm::vec3> n, std::vector<unsigned int> i,
                                                           std::vector<glm::vec3> t, std::vector<glm::vec3> b) {
    GLuint vao, vbo, ebo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    std::vector<float> interleaved_data = generate_interleave_buffer_vuvnbit(v, uv, n, t, b);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, interleaved_data.size() * sizeof(float), &interleaved_data[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, i.size() * sizeof(unsigned int), &i[0], GL_STATIC_DRAW);

    generate_vertex_attrib_array(v, uv, n, t, b);

    glBindVertexArray(0);

    kE::Primitive::Mesh mesh(vao, vbo, ebo, i.size());
    return mesh;
}

Kiwi::Engine::Renderer::Texture
Kiwi::Engine::Asset::Loader::createMap(std::string source, Kiwi::Engine::Renderer::Texture::Type type, bool alpha) {
    int w, h, comp;
    stbi_set_flip_vertically_on_load(true);


    unsigned char *image = nullptr;
    if (alpha)
        image = stbi_load(source.c_str(), &w, &h, &comp, STBI_rgb_alpha);
    else
        image = stbi_load(source.c_str(), &w, &h, &comp, STBI_default);

    if (!image)
        throw std::runtime_error(std::string(stbi_failure_reason()) + " : " + source);

    GLenum format;
    if (comp == 1)
        format = GL_RED;
    else if (comp == 2)
        format = GL_RG;
    else if (comp == 3)
        format = GL_RGB;
    else if (comp == 4) {
        format = GL_RGBA;
        std::cout << "Found alpha!" << std::endl;
    }
    else
        throw std::invalid_argument("Texture has invalid format: " + source);

    GLuint texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(image);
    return kE::Renderer::Texture(GL_TEXTURE_2D, texture, type);
}

Kiwi::Engine::Renderer::Texture Kiwi::Engine::Asset::Loader::createCubeMap(std::vector<const char *> sources) {
    GLuint textureID;
    glGenTextures(1, &textureID);

    stbi_set_flip_vertically_on_load(false);

    int width, height, comp;
    unsigned char *image;

    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    for (GLuint i = 0; i < sources.size(); i++) {
        image = stbi_load(sources[i], &width, &height, &comp, STBI_default);

        if (image == nullptr)
            throw std::runtime_error(std::string(stbi_failure_reason()));

        GLenum format;
        if (comp == 3)
            format = GL_RGB;
        else
            format = GL_RGBA;
        glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
                format, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image
        );
        stbi_image_free(image);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    return kE::Renderer::Texture(GL_TEXTURE_CUBE_MAP, textureID, kE::Renderer::Texture::Type::CUBE_MAP);
}


