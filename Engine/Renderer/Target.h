//
// Created by Raphael DANTZER on 12/4/16.
//

#ifndef KIWIENGINE_BUFFER_H
#define KIWIENGINE_BUFFER_H

#include "../../Core/Graphics.h"
#include "../Primitives/Mesh.h"
#include "Program.h"

namespace Kiwi { namespace Engine { namespace Renderer {
            class Target {
            public:
                Target() {};
                Target(int width, int height);
                ~Target();

                void bindFrame() const;
                void renderFrame(GLProgram shader) const;

            private:
                GLuint                  _fbo;
                GLuint                  _rbo;
                Primitive::Mesh         _mesh;
                GLuint                  _texture;
            };
        }
    }
}

#endif //KIWIENGINE_BUFFER_H
