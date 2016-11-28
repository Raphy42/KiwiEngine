//
// Created by Raphaël Dantzer on 23/11/16.
//

#ifndef KIWIENGINE_SHADERBUILDER_H
#define KIWIENGINE_SHADERBUILDER_H

#include <vector>
#include "Shader.h"
#include "Program.h"
#include "../../Core/Graphics.h"

namespace Kiwi {
    namespace Engine {
        namespace Renderer {
            class ShaderBuilder {
            public:
                ShaderBuilder();

                ~ShaderBuilder();

                Shader<GLuint> createFromFile(GLenum type, const std::string source);

            private:
                GLint _status;

            };

        }
    }
}


#endif //KIWIENGINE_SHADERBUILDER_H
