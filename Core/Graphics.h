//
// Created by Raphaël Dantzer on 23/11/16.
//

#ifndef KIWIENGINE_COREGRAPHICS_H
#define KIWIENGINE_COREGRAPHICS_H

//todo handle cross platform
#if defined(__APPLE__)

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include <OpenCL/cl_gl.h>
#include <OpenCL/cl_gl_ext.h>
#include <OpenGL/OpenGL.h>

#include <Opengl/gl3.h>

#elif defined(__linux__)

#warning "Not implemented yet need to add glad.h"

#endif

#endif //KIWIENGINE_COREGRAPHICS_H
