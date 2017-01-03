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

                virtual void bind(unsigned int slot) override;

                virtual Shading::Type getType() const override;

                virtual void setVec3Parameter(std::string name, glm::vec3 value) override;

                virtual void setParameter(std::string name, float value) override;

                virtual void bindShader(GLProgram shader) override;

                virtual void addMap(Texture texture) override;

                virtual void setFlag(std::string name, bool value) override;

                glm::vec3 _color;
            private:


                void update();

                GLProgram _shader;
                std::unordered_map<std::string, GLint> _locationMap;

                glm::vec3 _diffuse;
                glm::vec3 _ambient;
                glm::vec3 _specular;
                float _shininess;
                bool _dirty;
            };

        }
    }
}

#endif //KIWIENGINE_PHONGMATERIAL_H
