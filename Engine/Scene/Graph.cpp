//
// Created by Raphael DANTZER on 12/22/16.
//

#include "Graph.h"

unsigned long
Kiwi::Engine::Scene::Graph::add(GraphData *data) {
    _data.push_back(data);
    return _data.size();
}

Kiwi::Engine::Scene::GraphData *
Kiwi::Engine::Scene::Graph::getFromRaytrace(const std::pair<glm::vec3, glm::vec3> &ray) {
    Primitive::AABB box(ray.first, ray.second);

    for (auto &it : _data) {
        auto intersection = it->bounds.intersect(box);
        switch (intersection) {
            case Primitive::AABB::Intersection::INSIDE:
            case Primitive::AABB::Intersection::INTERSECT:
                return it;
            case Primitive::AABB::Intersection::OUTSIDE:
                break;
        }
    }
    return nullptr;
}

Kiwi::Engine::Scene::GraphData *
Kiwi::Engine::Scene::Graph::getFromIndex(unsigned int index) {
    return _data.at(index);
}

void Kiwi::Engine::Scene::Graph::removeFromIndex(unsigned int index) {
    _data.erase(_data.begin() + index);
}

Kiwi::Engine::Scene::GraphData *
Kiwi::Engine::Scene::GraphFactory::create(Kiwi::Engine::Primitive::Mesh mesh,
                                                                          Kiwi::Engine::Renderer::Material *material,
                                                                          std::pair<glm::vec3, glm::vec3> bounds,
                                                                          Actuator *actuator)
{
    GraphData   *data;

    data = new GraphData();
    data->material = material;
    data->mesh = mesh;
    data->bounds = Primitive::AABB(bounds.first, bounds.second);
    data->actuator = (actuator ? actuator : new Actuator);
    return data;
}
