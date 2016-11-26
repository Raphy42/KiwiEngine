//
// Created by Raphaël Dantzer on 26/11/16.
//

#ifndef KIWIENGINE_MESH_H
#define KIWIENGINE_MESH_H

#include "../../Core/CoreGraphics.h"

namespace Kiwi {
    namespace Engine {
        namespace Primitive {
            class Mesh {
            private:
                GLuint _vao;
                GLuint _vbo;
                GLuint _ebo;
            };
        }
    }
}

#endif //KIWIENGINE_MESH_H
