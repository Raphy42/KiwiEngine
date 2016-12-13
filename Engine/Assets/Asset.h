//
// Created by Raphael DANTZER on 12/13/16.
//

#ifndef KIWIENGINE_ASSET_H
#define KIWIENGINE_ASSET_H

#include <string>
#include "../Primitives/Mesh.h"
#include "../Renderer/Material.h"
#include "../Primitives/AABB.h"

namespace Kiwi {
    namespace Engine {
        namespace Asset {
            class Asset {
            public:
                enum class Type : int {
                    SCENE,
                    PROP,
                };

                Asset() = default;

                Asset(std::string &name, Type &type);

                Asset(std::string &name, Type &type, std::shared_ptr<Primitive::Mesh> mesh,
                      std::shared_ptr<Renderer::Material> material);

                virtual ~Asset() {};

                Type getType(void) const;

                Primitive::AABB getBounds(void) const;

                void setBounds(Primitive::AABB &bounds);

            private:
                std::string _name;
                Type _type;

                std::shared_ptr<Primitive::Mesh> _mesh;
                std::shared_ptr<Renderer::Material> _material;

                Primitive::AABB _bounds;
            };
        }
    }
}

#endif //KIWIENGINE_ASSET_H
