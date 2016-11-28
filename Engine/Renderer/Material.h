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
                    DIFFUSE,
                    SPECULAR,
                    NORMAL
                };


                Material(Type type) : _type(type) {};

                Type getType(void) const {
                    return _type;
                }

                ~Material() {};

            private:
                Type _type;
            };
        }
    }
}


#endif //KIWIENGINE_MATERIAL_H
