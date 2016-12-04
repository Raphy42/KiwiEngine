//
// Created by Raphaël Dantzer on 04/12/16.
//

#ifndef KIWIENGINE_PHONGTEXTUREDMATERIAL_H
#define KIWIENGINE_PHONGTEXTUREDMATERIAL_H

#include "Material.h"

namespace Kiwi {
    namespace Engine {
        namespace Renderer {
            class PhongTexturedMaterial : public Material {
            public:
                PhongTexturedMaterial();

                virtual ~PhongTexturedMaterial() override = default;

                virtual void bind(unsigned int slot) override;

                virtual Shading::Type getType() const override;

                virtual void setParameter(std::string name, glm::vec3 value) override;

                virtual void bindShader(GLProgram shader) override;

                virtual void addMap(Texture texture) override;

            private:
                GLProgram _shader;
                std::unordered_map<std::string, GLint> _locationMap;
            };

        }
    }
}


#endif //KIWIENGINE_PHONGTEXTUREDMATERIAL_H
