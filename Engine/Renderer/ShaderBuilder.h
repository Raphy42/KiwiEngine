//
// Created by Raphaël Dantzer on 23/11/16.
//

#ifndef KIWIENGINE_SHADERBUILDER_H
#define KIWIENGINE_SHADERBUILDER_H

#include "Shader.h"

class ShaderBuilder
{
public:
    ShaderBuilder();
    ~ShaderBuilder();

    static ShaderBuilder    instance;

    Shader          *create(std::string &source) const;
private:

};


#endif //KIWIENGINE_SHADERBUILDER_H
