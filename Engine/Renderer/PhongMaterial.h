//
// Created by Raphaël Dantzer on 04/12/16.
//

#ifndef KIWIENGINE_PHONGMATERIAL_H
#define KIWIENGINE_PHONGMATERIAL_H

#include <glm/vec3.hpp>
#include <unordered_map>
#include <string>
#include "Material.h"
#include "Program.h"

namespace Kiwi {
    namespace Engine {
        namespace Renderer {
            class PhongMaterial : public Material {
            public:
                PhongMaterial();

                virtual ~PhongMaterial() = default;

                void setColor(glm::vec3 color);

                virtual void bindTextures(unsigned int slot) override;

                virtual Shading::Type getType() const override;

                virtual void setParameter(std::string name, glm::vec3 value) override;

                virtual void bindShader(GLProgram shader) override;

                virtual void addMap(Texture texture) override;

            private:
                void update();

                GLProgram _shader;
                std::unordered_map<std::string, GLint> _locationMap;
                glm::vec3 _color;
                bool _dirty;
            };

        }
    }
}

#endif //KIWIENGINE_PHONGMATERIAL_H
