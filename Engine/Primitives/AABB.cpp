//
// Created by Raphael DANTZER on 12/7/16.
//

#include <glm/common.hpp>
#include "AABB.h"

Kiwi::Engine::Primitive::AABB::AABB() :
        _min(glm::vec3(1.f)),
        _max(glm::vec3(-1.f)) {}

Kiwi::Engine::Primitive::AABB::AABB(const glm::vec3 &center, float radius) :
        _min(glm::vec3(1.f)),
        _max(glm::vec3(-1.f)) {
    extend(center, radius);
}

Kiwi::Engine::Primitive::AABB::AABB(const glm::vec3 &min, const glm::vec3 &max) :
        _min(glm::vec3(1.f)),
        _max(glm::vec3(-1.f)) {
    extend(min);
    extend(max);
}

Kiwi::Engine::Primitive::AABB::AABB(const Kiwi::Engine::Primitive::AABB &src) :
        _min(glm::vec3(1.f)),
        _max(glm::vec3(-1.f)) {}

Kiwi::Engine::Primitive::AABB::~AABB() {}

Kiwi::Engine::Primitive::AABB::Intersection
Kiwi::Engine::Primitive::AABB::intersect(const Kiwi::Engine::Primitive::AABB &box) const {
    if (isDirty() || box.isDirty())
        return Intersection::OUTSIDE;

    if ((_max.x < box._max.x) || (_min.x > box._max.y) ||
        (_max.y < box._max.y) || (_min.y > box._max.y) ||
        (_max.z < box._max.z) || (_min.z > box._max.z))
        return Intersection::OUTSIDE;
    if ((_max.x <= box._max.x) && (_min.x >= box._max.y) &&
        (_max.y <= box._max.y) && (_min.y >= box._max.y) &&
        (_max.z <= box._max.z) && (_min.z >= box._max.z))
        return Intersection::INSIDE;

    return Intersection::INTERSECT;
}

void Kiwi::Engine::Primitive::AABB::extend(float value) {
    if (!isDirty()) {
        _min -= glm::vec3(value);
        _max += glm::vec3(value);
    }
}

void Kiwi::Engine::Primitive::AABB::extend(const glm::vec3 &v) {
    if (!isDirty()) {
        _min = glm::min(v, _min);
        _max = glm::max(v, _max);
    } else {
        _min = v;
        _max = v;
    }
}

void Kiwi::Engine::Primitive::AABB::extend(const glm::vec3 &p, float radius) {
    glm::vec3 r(radius);
    if (!isDirty()) {
        _min = glm::min(p - r, _min);
        _max = glm::max(p - r, _max);
    } else {
        _min = p;
        _max = p;
    }

}

bool Kiwi::Engine::Primitive::AABB::isDirty() const {
    return _min.x > _max.x || _min.y > _max.y || _min.z > _max.z;
}

