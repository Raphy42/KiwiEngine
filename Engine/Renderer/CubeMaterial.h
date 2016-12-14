//
// Created by Raphael DANTZER on 12/4/16.
//

#ifndef KIWIENGINE_CUBEMATERIAL_H
#define KIWIENGINE_CUBEMATERIAL_H

#include "Material.h"

namespace Kiwi {
    namespace Engine {
        namespace Renderer {
            class CubeMaterial : public Material {
            public:
                CubeMaterial(Texture texture) : _cubemap(texture) {};

                virtual ~CubeMaterial() override = default;

                virtual void bind(unsigned int slot) override;

                virtual Shading::Type getType() const override;

                virtual void setVec3Parameter(std::string name, glm::vec3 value) override;

                virtual void setParameter(std::string name, float value) override;

                virtual void setFlag(std::string name, bool value) override;

                virtual void bindShader(GLProgram shader) override;

                virtual void addMap(Texture texture) override;

            private:
                Texture _cubemap;
                GLProgram _shader;
            };

        }
    }
}


#endif //KIWIENGINE_CUBEMATERIAL_H
