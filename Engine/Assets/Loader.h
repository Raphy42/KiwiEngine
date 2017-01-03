//
// Created by Raphael DANTZER on 11/27/16.
//

#ifndef KIWIENGINE_LOADER_H
#define KIWIENGINE_LOADER_H

#include <string>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include "../Primitives/Mesh.h"
#include "../Scene/Entity.h"
#include "../Scene/Graph.h"
#include "../../Core/Filesystem/VirtualFilesystem.h"

namespace Kiwi {
    namespace Engine {
        namespace Asset {
            namespace kE = Kiwi::Engine;

            class Loader {
            public:
                friend  Primitive::Mesh;

                enum class Type : int {
                    PLANE = 0x0,
                    CUBE,
                    SCREEN
                };

                enum class Target : GLenum {
                    FLAT = GL_TEXTURE_2D,
                    BOX = GL_SAMPLER_CUBE,
                };

                Loader() {
                    _textureCache.emplace("diffuse", createMap("./Assets/textures/uv-debug.jpg",
                                                               Renderer::Texture::Type::DIFFUSE));
                    _textureCache.emplace("normal",
                                          createMap("./Assets/textures/norm.png", Renderer::Texture::Type::NORMAL));
                    _textureCache.emplace("specular",
                                          createMap("./Assets/textures/black.png", Renderer::Texture::Type::SPECULAR));
                    _textureCache.emplace("alpha", createMap("./Assets/textures/white.png", Renderer::Texture::Type::ALPHA));
                };

                ~Loader() {};

                typedef std::vector<unsigned int> Indices;
                typedef std::vector<Renderer::Texture> Textures;

                Primitive::Mesh createDefaultMesh(Type type);

                Renderer::Texture createTexture(Target, std::string source);

                Renderer::Texture createMap(std::string source, Renderer::Texture::Type type, bool alpha = false);

                Renderer::Texture createCubeMap(std::vector<const char *> sources);

                Primitive::Mesh createMeshFromVertices(std::vector<float> v);

                Primitive::Mesh createMeshFromSimpleModel(const char *filename);

                Scene::Entity createEntityFromModel(const char *filename);

                Scene::Graph *createGraphFromModel(const char *filename, std::string name = "default");

                bool isValidFile(const fs::path &file) const;

            private:
                Primitive::Mesh createMeshVUVNStride(std::vector<glm::vec3> v,
                                                     std::vector<glm::vec2> uv,
                                                     std::vector<glm::vec3> n);

                Primitive::Mesh createMeshVUVNStrideIndexed(std::vector<glm::vec3> v,
                                                            std::vector<glm::vec2> uv,
                                                            std::vector<glm::vec3> n,
                                                            std::vector<unsigned int> i);

                Primitive::Mesh createMeshVUVNTBStrideIndexed(std::vector<glm::vec3> v,
                                                              std::vector<glm::vec2> uv,
                                                              std::vector<glm::vec3> n,
                                                              std::vector<unsigned int> i,
                                                              std::vector<glm::vec3> t, std::vector<glm::vec3> b);

                Primitive::Mesh createPlane(unsigned int x, unsigned int columns);

                Primitive::Mesh processAiMesh(aiMesh *mesh, const aiScene *aScene);
                Primitive::Mesh processAiMesh(aiMesh *mesh, const aiScene *aScene, std::pair<glm::vec3, glm::vec3> *box);

                Renderer::Texture
                loadMaterialTexture(aiMaterial *material, aiTextureType type, Renderer::Texture::Type map);


                std::string _path;
                std::unordered_map<std::string, kE::Renderer::Texture> _textureCache;
            };


        }
    }
}

#endif //KIWIENGINE_LOADER_H
