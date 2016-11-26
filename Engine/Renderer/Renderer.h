//
// Created by Raphaël Dantzer on 26/11/16.
//

#ifndef KIWIENGINE_RENDERER_H
#define KIWIENGINE_RENDERER_H

#include "../Primitives/Camera.h"

namespace Kiwi {
    namespace Engine {
        namespace Renderer {
            class Renderer {
            public:
                Renderer() {};

                void render();

            private:
                Primitive::Camera _camera;
            };
        }
    }
}

#endif //KIWIENGINE_RENDERER_H
