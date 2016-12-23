//
// Created by Raphael DANTZER on 12/7/16.
//

#include <glm/gtc/matrix_transform.hpp>
#include <chrono>
#include <stdexcept>
#include <glm/gtc/type_ptr.hpp>
#include "Actuator.h"

Kiwi::Engine::Scene::Actuator::Actuator() :
    _transform(glm::mat4()),
    _angle(0.f)
{
}

Kiwi::Engine::Scene::Actuator *
Kiwi::Engine::Scene::Actuator::position(glm::vec3 pos) {
    _pos = glm::translate(_pos, pos);
    _dirty = true;
    return this;
}

Kiwi::Engine::Scene::Actuator *
Kiwi::Engine::Scene::Actuator::setScale(glm::vec3 scale) {
    _scale = glm::scale(_scale, scale);
    _dirty = true;
    return this;
}

Kiwi::Engine::Scene::Actuator *
Kiwi::Engine::Scene::Actuator::rotate(glm::vec3 rotation, float angle) {
    _rotation = glm::rotate(_rotation, angle, rotation);
    _angle = angle;
    _dirty = true;
    return this;
}

glm::mat4 Kiwi::Engine::Scene::Actuator::update(void) {
    if (_dirty) {
        _transform = _pos * _scale * _rotation;
        _dirty = false;
    }
    return _transform;
}

Kiwi::Engine::Scene::Actuator *Kiwi::Engine::Scene::Actuator::ease(Kiwi::Engine::GUI::Easing ease, float duration) {
    throw std::runtime_error("Unimplemented");
    if (_duration == 0)
        _duration = duration;
    if (_duration)
    {
        _duration--;
    }
}

void Kiwi::Engine::Scene::Actuator::recompose(float *t, float *r, float *s) {
    _rotation = glm::make_mat4(r);
    _pos = glm::make_mat4(t);
    _scale = glm::make_mat4(s);
    _dirty = true;
}

void Kiwi::Engine::Scene::Actuator::recompose(glm::mat4 &transform) {
    _transform = transform;
    _dirty = false;
}


