//
// Created by Raphaël Dantzer on 04/12/16.
//

#ifndef KIWIENGINE_SHADING_H
#define KIWIENGINE_SHADING_H

namespace Kiwi {
    namespace Engine {
        namespace Renderer {
            struct Shading {
                enum class Type : int {
                    DEFAULT = 0x0,
                    PHONG = 0x1,
                    PHONG_TEXTURED = 0x2,
                    PBR = 0x3,
                    POST_PROCESS = 0x4,
                    SKYBOX = 0x5,

                    DEBUG = 0xf         //last enum so we can _shaders.reserve(DEBUG)
                };
            };
        }
    }
}

#endif //KIWIENGINE_SHADING_H
