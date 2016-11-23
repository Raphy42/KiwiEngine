//
// Created by Raphaël Dantzer on 23/11/16.
//

#ifndef KIWIENGINE_TEXTURE_H
#define KIWIENGINE_TEXTURE_H

#include <vector>
#include "../../Core/CoreGraphics.h"

template <typename Type, typename Bind>
class Texture {
public:
    Texture(Type type, Bind bind) :
            _type(type),
            _bind(bind)
            {}

    ~Texture()
    {
        static_assert(std::is_same<Bind, GLuint>::value, "No known destructor for type");
        glDeleteTextures(1, &_bind);
    }

    template <typename Slot>
    void
    bind(Slot slot)
    {
        glActiveTexture(slot);
        glBindTexture(_type, _bind);
    }

private:

    Type            _type;
    Bind            _bind;
};


#endif //KIWIENGINE_TEXTURE_H
