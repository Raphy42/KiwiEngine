//
// Created by Raphael DANTZER on 11/23/16.
//

#include <fstream>
#include "ShaderBuilder.h"

ShaderBuilder::ShaderBuilder() {

}

ShaderBuilder::~ShaderBuilder() {

}

Shader<GLuint> *ShaderBuilder::createFromFile(GLenum type, const std::string source) {
    GLuint shader;
    const GLchar *s = source.c_str();

    shader = glCreateShader(type);
    glShaderSource(shader, 1, &s, nullptr);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &_status);
    if (!_status) {
        GLchar log[512];

        glGetShaderInfoLog(shader, 512, nullptr, log);
        //todo do something with log
    }
    return new Shader<GLuint>(shader);
}


