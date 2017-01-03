//
// Created by Raphael DANTZER on 12/22/16.
//

#include "Graph.h"

unsigned long
Kiwi::Engine::Scene::Graph::add(GraphData *data) {
    _data.push_back(data);
    _dirty = true;
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

std::vector<Kiwi::Engine::Scene::GraphData *> Kiwi::Engine::Scene::Graph::data() const {
    return _data;
}

bool Kiwi::Engine::Scene::Graph::isDirty() const {
    return _dirty;
}

void Kiwi::Engine::Scene::Graph::setDirty(bool dirty) {
    _dirty = dirty;
}

const std::string &Kiwi::Engine::Scene::Graph::getName() const {
    return _name;
}

void Kiwi::Engine::Scene::Graph::setName(const std::string &name) {
    _name = name;
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

Kiwi::Engine::Scene::GraphData *
Kiwi::Engine::Scene::GraphFactory::create(Kiwi::Engine::Primitive::Mesh mesh,
                                          Kiwi::Engine::Renderer::Material *material,
                                          Kiwi::Engine::Primitive::AABB &bounds,
                                          Actuator *actuator)
{
    GraphData   *data;

    data = new GraphData();
    data->material = material;
    data->mesh = mesh;
    data->bounds = bounds;
    data->actuator = (actuator ? actuator : new Actuator);
    return data;
}
