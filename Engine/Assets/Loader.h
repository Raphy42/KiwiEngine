//
// Created by Raphael DANTZER on 11/27/16.
//

#ifndef KIWIENGINE_LOADER_H
#define KIWIENGINE_LOADER_H

#include <string>
#include <assimp/Importer.hpp>
#include "../Primitives/Mesh.h"
#include "../Primitives/Model.h"

namespace Kiwi { namespace Engine { namespace Asset {
            namespace kE = Kiwi::Engine;

            class Loader
            {
            public:
                friend  Primitive::Mesh;
                friend  Primitive::Model;

                enum class Type : int {
                    PLANE = 0x0,
                    CUBE
                };

                enum class Target : GLenum {
                    FLAT = GL_TEXTURE_2D,
                    BOX = GL_SAMPLER_CUBE,
                };

                Loader() {};
                ~Loader() {};

                typedef std::vector<Primitive::Vertex>              Vertices;
                typedef std::vector<unsigned int>                   Indices;
                typedef std::vector<Renderer::Texture>              Textures;

                kE::Primitive::Mesh                     createDefaultMesh(Type type);
                kE::Primitive::Mesh                     createMeshFromAttributes(Vertices v, Indices i, Textures t);
                kE::Primitive::Mesh                     createMeshVUVNStride(std::vector<float> v,
                                                                             std::vector<float> uv,
                                                                             std::vector<float> n);

                kE::Renderer::Texture                   createTexture(Target, std::string source);

                kE::Primitive::Mesh                     createMeshFromVertices(std::vector<float> v);
                kE::Primitive::Model                    createModel(std::string source);

            private:
//                void                            processNode(kE::Primitive::Model *model, aiNode *node, const aiScene *scene);
//                kE::Primitive::Mesh             processMesh(aiMesh *mesh, const aiScene *scene);
//                kE::Renderer::Texture           processTexture(aiMaterial *material, aiTextureType type, std::string name);
//                Textures                        processTextures(aiMaterial *material, aiTextureType type, std::string name);

                Assimp::Importer                _importer;

            };


        }
    }
}

#endif //KIWIENGINE_LOADER_H
