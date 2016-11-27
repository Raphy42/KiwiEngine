//
// Created by Raphael DANTZER on 11/27/16.
//

#ifndef KIWIENGINE_MODEL_H
#define KIWIENGINE_MODEL_H

#include "Mesh.h"

namespace Kiwi {
namespace Engine {
namespace Primitive {
    class Model
    {
    public:
        Model() {};
        ~Model() {};

    protected:
        std::vector<Mesh>       _meshes;
    };
}
}
}

#endif //KIWIENGINE_MODEL_H
