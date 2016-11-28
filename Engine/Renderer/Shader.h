//
// Created by Raphaël Dantzer on 23/11/16.
//

#ifndef KIWIENGINE_SHADER_H
#define KIWIENGINE_SHADER_H

#include <algorithm>
#include "../../Core/Graphics.h"

template <typename Bind>
class Shader
{
public:
    Shader(Bind bind) : _bind(bind) {}

    Bind getBind() { return _bind; }

private:
    Bind            _bind;
};

typedef Shader<GLuint> GLShader;

#endif //KIWIENGINE_SHADER_H
