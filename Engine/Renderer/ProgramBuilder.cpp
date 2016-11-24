//
// Created by Raphael DANTZER on 11/24/16.
//

#include "ProgramBuilder.h"

ProgramBuilder::ProgramBuilder() {

}

ProgramBuilder::~ProgramBuilder() {

}

Program<GLuint> *ProgramBuilder::createProgramFromShaders(Shader<GLuint> vs, Shader<GLuint> fs) {
    GLuint program;

    program = glCreateProgram();
    glAttachShader(program, vs.getBind());
    glAttachShader(program, fs.getBind());
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &_status);
    if (!_status) {
        char log[512];

        glGetProgramInfoLog(program, 512, nullptr, log);
        //todo do something with log
    }
    return new Program<GLuint>(program);
}
