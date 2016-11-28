//
// Created by Raphaël Dantzer on 23/11/16.
//

#ifndef KIWIENGINE_COREGRAPHICS_H
#define KIWIENGINE_COREGRAPHICS_H

//todo handle cross platform
#if defined(GLAD_DEBUG)
#include <glad/glad.h>
extern "C" = void pre_gl_call(const char *name, void *f, int length, ...)
    { printf("Calling: %s (%d arguments)\n", name, length); }

    glad_set_pre_callback(pre_gl_call);
#elif defined(__APPLE__)

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

#include <Opengl/gl3.h>

#elif defined(__linux__)

#error "Not implemented yet need to add glad.h"
#include "glad.h"

#endif

#endif //KIWIENGINE_COREGRAPHICS_H
