//
// Created by Raphaël Dantzer on 23/11/16.
//

#ifndef KIWIENGINE_TEXTURE_H
#define KIWIENGINE_TEXTURE_H

#include <vector>
#include "../../Core/Graphics.h"

namespace Kiwi { namespace Engine { namespace Renderer {
            class Texture
            {
            public:
                Texture() : _target(GL_TEXTURE_2D), _id(0) {};
                Texture(GLenum target, GLuint id) :
                        _target(target),
                        _id(id)
                {
                };

                void        bind() const {
                    glBindTexture(GL_TEXTURE_2D, _id);
                }

            private:
                GLenum      _target;
                GLuint      _id;
            };
        }
    }
}

#endif //KIWIENGINE_TEXTURE_H
