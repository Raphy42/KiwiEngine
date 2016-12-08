//
// Created by Raphael DANTZER on 12/7/16.
//

#include <glm/gtc/matrix_transform.hpp>
#include <chrono>
#include <stdexcept>
#include "Actuator.h"

Kiwi::Engine::Scene::Actuator::Actuator() :
    _transform(glm::mat4()),
    _pos(glm::vec3()),
    _rotation(glm::vec3(1.f)),
    _scale(glm::vec3(1.f)),
    _angle(0.f)
{
}

Kiwi::Engine::Scene::Actuator *
Kiwi::Engine::Scene::Actuator::position(glm::vec3 pos) {
    _pos = pos;
    return this;
}

Kiwi::Engine::Scene::Actuator *
Kiwi::Engine::Scene::Actuator::setScale(glm::vec3 scale) {
    _scale = scale;
    return this;
}

Kiwi::Engine::Scene::Actuator *
Kiwi::Engine::Scene::Actuator::rotate(glm::vec3 rotation, float angle) {
    _rotation = rotation;
    _angle = angle;
    return this;
}

glm::mat4 Kiwi::Engine::Scene::Actuator::update(void) {
    glm::mat4 pos       = glm::translate(glm::mat4(), _pos);
    glm::mat4 scale     = glm::scale(glm::mat4(), _scale);
    glm::mat4 rotation  = glm::rotate(glm::mat4(), _angle, _rotation);

    _transform = pos * scale * rotation;
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


