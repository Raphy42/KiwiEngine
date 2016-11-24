//
// Created by Raphael DANTZER on 11/24/16.
//

#ifndef KIWIENGINE_PROGRAMBUILDER_H
#define KIWIENGINE_PROGRAMBUILDER_H


#include "../../Core/CoreGraphics.h"
#include "Program.h"
#include "Shader.h"

class ProgramBuilder {
public:
    ProgramBuilder();

    ~ProgramBuilder();

    Program<GLuint> *createProgramFromShaders(Shader<GLuint> vs, Shader<GLuint> fs);

private:
    GLint _status;
};


#endif //KIWIENGINE_PROGRAMBUILDER_H
