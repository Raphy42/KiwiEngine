//
// Created by Raphael DANTZER on 12/22/16.
//

#ifndef KIWIENGINE_GRAPH_H
#define KIWIENGINE_GRAPH_H

#include "../Primitives/AABB.h"
#include "../Primitives/Mesh.h"
#include "../Renderer/Material.h"
#include "Actuator.h"

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
                std::string         name;
                //Todo uuid
            };

            class Graph {
            public:
                Graph() = default;

                unsigned long add(GraphData *data);

                GraphData *getFromRaytrace(const std::pair<glm::vec3, glm::vec3> &ray);

                GraphData *getFromIndex(unsigned int index);

                void removeFromIndex(unsigned int index);

                std::vector<GraphData *> data() const;

                bool isDirty() const;

                void setDirty(bool dirty);

                const std::string &getName() const;

                void setName(const std::string &_name);

            protected:
                std::vector<GraphData *>    _data;
                std::string                 _name;

                bool        _dirty = true;
            };

            class GraphFactory {
            public:
                static GraphData *create(Primitive::Mesh mesh, Renderer::Material *material,
                                         std::pair<glm::vec3, glm::vec3> bounds, Actuator *actuator = nullptr);
            };
        }
    }
}


#endif //KIWIENGINE_GRAPH_H
