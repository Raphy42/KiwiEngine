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
                enum class TextureType : int {
                    DIFFUSE = 0x0,
                    SPECULAR,
                    NORMAL
                };

                Texture     &getTexture(TextureType type) const {
                    return _texture[static_cast<int>(type)];
                }

            private:
                std::shared_ptr<Shader>     _shader;
                std::vector<Texture>        _texture;
            };
        }
    }
}


#endif //KIWIENGINE_MATERIAL_H
