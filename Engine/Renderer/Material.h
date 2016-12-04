//
// Created by Raphaël Dantzer on 23/11/16.
//

#ifndef KIWIENGINE_MATERIAL_H
#define KIWIENGINE_MATERIAL_H

#include <memory>
#include <string>
#include <unordered_map>
#include <glm/vec3.hpp>
#include "Shader.h"
#include "Texture.h"
#include "Shading.h"
#include "Program.h"

namespace Kiwi { namespace Engine { namespace Renderer {
            class Material
            {
            public:
                Material() {};

                virtual ~Material() = default;

                virtual void bind(unsigned int slot) = 0;

                virtual Shading::Type getType() const = 0;

                virtual void setParameter(std::string name, glm::vec3 value) = 0;

                virtual void bindShader(GLProgram shader) = 0;

                virtual void addMap(Texture texture) = 0;

            };
        }
    }
}


#endif //KIWIENGINE_MATERIAL_H
