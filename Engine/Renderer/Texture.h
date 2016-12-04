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
                enum class Type : int {
                    ALBEDO,
                    NORMAL,
                    SPECULAR,
                    ROUGHNESS,
                    METALLIC,
                    HEIGHT
                };


                Texture() : _target(GL_TEXTURE_2D), _id(0) {};
                Texture(GLenum target, GLuint id) :
                        _target(target),
                        _id(id),
                        _type(Type::ALBEDO)
                {};

                Texture(GLenum target, GLuint id, Type type) :
                        _target(target),
                        _id(id),
                        _type(type)
                {};

                void        bind() const {
                    glBindTexture(_target, _id);
                }

                Type        getType() const {
                    return _type;
                }

            private:
                GLenum      _target;
                GLuint      _id;
                Type _type;
            };
        }
    }
}

#endif //KIWIENGINE_TEXTURE_H
