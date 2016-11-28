//
// Created by Raphael DANTZER on 11/24/16.
//

#include "ProgramBuilder.h"
#include "../Event/CoreNotifier.h"

namespace Kiwi {
    namespace Engine {
        namespace Renderer {
            ProgramBuilder::ProgramBuilder() {

            }

            ProgramBuilder::~ProgramBuilder() {

            }

            GLProgram ProgramBuilder::createProgramFromShaders(GLShader vs, GLShader fs) {
                GLuint program;

                program = glCreateProgram();
                glAttachShader(program, vs.getBind());
                glAttachShader(program, fs.getBind());
                glLinkProgram(program);
                glGetProgramiv(program, GL_LINK_STATUS, &_status);
                if (!_status) {
                    char log[512];

                    glGetProgramInfoLog(program, 512, nullptr, log);

                    Event::Type::CoreEvent event;
                    event.type = Event::Type::CoreInteraction::SHADER_LINK_ERROR;
                    event.message = std::string(log);
                    Event::CoreNotifier::getInstance()->notify(event);
                }
                GLProgram p = GLProgram(program);
                return p;
            }

        }
    }
}