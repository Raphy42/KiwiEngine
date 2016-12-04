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

                Material()  : _type(Type::TEST) {};

                Material(Type type) : _type(type) {};
                Material(Texture texture) : _diffuse(texture) {};
                Material(Texture texture, Type type) : _diffuse(texture), _type(type) {};
                ~Material() {};

                void bind(unsigned int slot) const;

                void addMap(Texture texture);

                Type getType() const;

            private:
                std::vector<Texture>        _textures;
                Texture                     _diffuse;
                Texture                     _normal;
                Type                        _type;
            };
        }
    }
}


#endif //KIWIENGINE_MATERIAL_H
