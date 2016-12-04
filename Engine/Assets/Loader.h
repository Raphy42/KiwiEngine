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
#include "../Primitives/Model.h"
#include "../Scene/Entity.h"

namespace Kiwi {
    namespace Engine {
        namespace Asset {
            namespace kE = Kiwi::Engine;

            class Loader {
            public:
                friend  Primitive::Mesh;
                friend  Primitive::Model;

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
                    _textureCache.emplace("diffuse", createMap("./Assets/textures/ponpon.png",
                                                               Renderer::Texture::Type::DIFFUSE));
                    _textureCache.emplace("normal",
                                          createMap("./Assets/textures/norm.png", Renderer::Texture::Type::NORMAL));
                    _textureCache.emplace("specular",
                                          createMap("./Assets/textures/black.png", Renderer::Texture::Type::SPECULAR));
                };

                ~Loader() {};

                typedef std::vector<Primitive::Vertex> Vertices;
                typedef std::vector<unsigned int> Indices;
                typedef std::vector<Renderer::Texture> Textures;

                Primitive::Mesh createDefaultMesh(Type type);

                Primitive::Mesh createMeshFromAttributes(Vertices v, Indices i, Textures t);

                Renderer::Texture createTexture(Target, std::string source);

                Renderer::Texture createMap(std::string source, Renderer::Texture::Type type);

                Primitive::Mesh createMeshFromVertices(std::vector<float> v);

                Primitive::Mesh createMeshFromSimpleModel(const char *filename);

                Scene::Entity createEntityFromModel(const char *filename);

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

                Renderer::Texture
                loadMaterialTexture(aiMaterial *material, aiTextureType type, Renderer::Texture::Type map);


                std::string _path;
                std::unordered_map<std::string, kE::Renderer::Texture> _textureCache;
            };


        }
    }
}

#endif //KIWIENGINE_LOADER_H
