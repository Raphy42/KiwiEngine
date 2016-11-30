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
                    LOULE
                };

                Material(Type type) : _type(type) {};
                Material(Texture texture) : _diffuse(texture) {};
                Material(Texture texture, Type type) : _diffuse(texture), _type(type) {};

                void bind() const {
                    _diffuse.bind();
                }

                ~Material() {};

                Type getType() {
                    return _type;
                }

            private:
                Texture         _diffuse;
                Type            _type;
            };
        }
    }
}


#endif //KIWIENGINE_MATERIAL_H
