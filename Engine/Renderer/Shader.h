//
// Created by Raphaël Dantzer on 23/11/16.
//

#ifndef KIWIENGINE_SHADER_H
#define KIWIENGINE_SHADER_H

#include <algorithm>

template <typename Bind>
class Shader
{
public:
    Shader(Bind bind) : _bind(bind) {}

    Bind &getBind() { return _bind; }

private:
    Shader &operator = (const Shader &rhs)
    {
        static_assert(this != &rhs, "cant self assign");
        *this->_bind = rhs._bind;
        return *this;
    }

    Bind            _bind;
};

#endif //KIWIENGINE_SHADER_H
