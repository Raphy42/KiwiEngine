//
// Created by Raphaël Dantzer on 28/11/16.
//

#ifndef KIWIENGINE_STORAGE_H
#define KIWIENGINE_STORAGE_H

#include "../Primitives/Mesh.h"
#include "../Renderer/Texture.h"
#include "../Renderer/Program.h"

#include <unordered_map>
#include <string>

namespace Kiwi {
    namespace Engine {
        namespace Asset {
            class Storage {
            public:
                Storage() {};

                ~Storage() {};

                void storeMesh(Primitive::Mesh mesh, std::string name) {
                    _meshes[name] = mesh;
                }

                Primitive::Mesh getMesh(std::string name) const {
                    return _meshes.at(name);
                }

                void storeTexture(Renderer::Texture texture, std::string name) {
                    _textures[name] = texture;
                }

                Renderer::Texture getTexture(std::string name) const {
                    return _textures.at(name);
                }

//                void storeShader(GLProgram program, std::string name) {
//                    _shaders[name] = program;
//                }
//
//                GLProgram getShader(std::string name) const {
//                    return _shaders.at(name);
//                }

            private:
                std::unordered_map<std::string, Primitive::Mesh>        _meshes;
                std::unordered_map<std::string, Renderer::Texture>      _textures;
//                std::unordered_map<std::string, GLProgram>            _shaders;
            };
        }
    }
}

#endif //KIWIENGINE_STORAGE_H
