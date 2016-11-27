//
// Created by Raphael DANTZER on 11/27/16.
//

#ifndef KIWIENGINE_LOADER_H
#define KIWIENGINE_LOADER_H

#include "../Primitives/Mesh.h"

namespace Kiwi { namespace Engine { namespace Asset {
            namespace kE = Kiwi::Engine;

            class Loader
            {
            public:
                Loader() {};
                ~Loader() {};

                typedef std::vector<Primitive::Vertex>              Vertices;
                typedef std::vector<unsigned int>                   Indices;
                typedef std::vector<Renderer::Texture>              Textures;

                virtual kE::Primitive::Mesh     *createMeshFromAsset(void) = 0;
                kE::Primitive::Mesh             *createMeshFromAttributes(Vertices v, Indices i, Textures t);

            private:

            };


        }
    }
}

#endif //KIWIENGINE_LOADER_H
