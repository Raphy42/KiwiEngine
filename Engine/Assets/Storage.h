//
// Created by Raphaël Dantzer on 28/11/16.
//

#ifndef KIWIENGINE_STORAGE_H
#define KIWIENGINE_STORAGE_H

#include "../Primitives/Mesh.h"

namespace Kiwi {
    namespace Engine {
        namespace Asset {
            class Storage {
            public:
                Storage() {};

                ~Storage() {};

                unsigned int storeMesh(Primitive::Mesh mesh) {
                    _meshes.push_back(mesh);
                    return static_cast<unsigned int>(_meshes.size());
                }

                Primitive::Mesh retrieveMesh(unsigned int id) const {
                    return _meshes.at(id);
                }

            private:
                std::vector<Primitive::Mesh> _meshes;
            };
        }
    }
}

#endif //KIWIENGINE_STORAGE_H
