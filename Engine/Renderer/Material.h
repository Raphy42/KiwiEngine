//
// Created by Raphaël Dantzer on 23/11/16.
//

#ifndef KIWIENGINE_MATERIAL_H
#define KIWIENGINE_MATERIAL_H

#include <memory>
#include <unordered_map>
#include "Shader.h"
#include "Texture.h"

namespace Kiwi { namespace Engine { namespace Renderer {
            class Material
            {
            public:
                enum class Type : int {
                    TEST = 0x0,
                    BASIC_LIGHTING,
                    PBR,
                    PHONG,
                    CUSTOM,
                };

                Material(Type type) : _type(type) {};
                Material(Texture texture) : _diffuse(texture) {};
                Material(Texture texture, Type type) : _diffuse(texture), _type(type) {};
                Material(std::pair<Texture, Texture> textures, Type type) :
                        _diffuse(textures.first),
                        _normal(textures.second),
                        _type(type),
                        _hasNormals(true)
                {};

                void bind(unsigned int slot) const {
                    glActiveTexture(GL_TEXTURE0 + slot);
                    _diffuse.bind();
                    if (_hasNormals)
                    {
                        glActiveTexture(GL_TEXTURE0 + slot + 1);
                        _normal.bind();
                    }
                }

                ~Material() {};

                Type getType() {
                    return _type;
                }

            private:
                bool            _hasNormals = false;
                Texture         _diffuse;
                Texture         _normal;
                Type            _type;
            };
        }
    }
}


#endif //KIWIENGINE_MATERIAL_H
