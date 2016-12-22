//
// Created by Raphael DANTZER on 12/22/16.
//

#ifndef KIWIENGINE_GRAPH_H
#define KIWIENGINE_GRAPH_H

#include "../Primitives/AABB.h"
#include "../Primitives/Mesh.h"
#include "Entity.h"
#include "../../Core/bsp.h"
#include "../Renderer/Renderer.h"

namespace Kiwi {
    namespace Engine {
        namespace Scene {

            /**
             * GraphData is declared as a struct, I can now modify the internals of GraphNode without breaking
             * everything
             */

            struct GraphData {
                GraphData() :
                        bounds(glm::vec3(-1.f), glm::vec3(1.f)),
                        actuator(nullptr) {}

                Primitive::AABB     bounds;
                Primitive::Mesh     mesh;
                Renderer::Material  *material;
                Actuator            *actuator;
            };

            class Graph {
            public:
                Graph() = default;

                unsigned long add(GraphData *data);

                GraphData *getFromRaytrace(const std::pair<glm::vec3, glm::vec3> &ray);

                GraphData *getFromIndex(unsigned int index);

                void removeFromIndex(unsigned int index);

            private:
                friend                          Renderer::Renderer;

                std::vector<GraphData *> _data;
            };

            class GraphFactory {
                static GraphData *create(Primitive::Mesh mesh, Renderer::Material *material,
                                         std::pair<glm::vec3, glm::vec3> bounds, Actuator *actuator = nullptr);
            };
        }
    }
}


#endif //KIWIENGINE_GRAPH_H
