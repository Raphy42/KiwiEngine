//
// Created by Raphael DANTZER on 11/24/16.
//

#ifndef KIWIENGINE_PROGRAMBUILDER_H
#define KIWIENGINE_PROGRAMBUILDER_H


#include "../../Core/Graphics.h"
#include "Program.h"
#include "Shader.h"

namespace Kiwi {
    namespace Engine {
        namespace Renderer {
            class ProgramBuilder {
            public:
                ProgramBuilder();

                ~ProgramBuilder();

                GLProgram createProgramFromShaders(GLShader vs, GLShader fs);

            private:
                GLint _status;
            };
        }
    }
}



#endif //KIWIENGINE_PROGRAMBUILDER_H
