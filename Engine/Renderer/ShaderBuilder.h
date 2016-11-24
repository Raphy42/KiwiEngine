//
// Created by Raphaël Dantzer on 23/11/16.
//

#ifndef KIWIENGINE_SHADERBUILDER_H
#define KIWIENGINE_SHADERBUILDER_H

#include <vector>
#include "Shader.h"
#include "Program.h"
#include "../../Core/CoreGraphics.h"

class ShaderBuilder
{
public:
    ShaderBuilder();
    ~ShaderBuilder();

    static ShaderBuilder    instance;

    Shader<GLuint> *createFromFile(GLenum type, const std::string source);

private:
    GLint _status;
};


#endif //KIWIENGINE_SHADERBUILDER_H
