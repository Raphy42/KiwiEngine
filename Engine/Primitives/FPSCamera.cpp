//
// Created by Raphaël Dantzer on 26/11/16.
//

#include "FPSCamera.h"

Kiwi::Engine::Primitive::FPSCamera::FPSCamera() :
        _position(glm::vec3(0.f, 0.f, 0.f)),
        _front(glm::vec3(0.f, 0.f, -1.f)),
        _up(glm::vec3(0.f, 1.f, 0.f)),
        _right(glm::vec3(1.f, 0.f, 0.f)),
        _yaw(-90.f),
        _pitch(0.f),
        _speed(glm::radians(1.f)),
        _sensitivity(0.25f),
        _zoom(68.f),
        _worldUp(0.f, 1.f, 0.f)
{}

Kiwi::Engine::Primitive::FPSCamera::FPSCamera(glm::vec3 position, glm::vec3 up) :
        _position(position),
        _front(glm::vec3(0.f, 0.f, -1.f)),
        _up(up),
        _right(glm::vec3(1.f, 0.f, 0.f)),
        _yaw(-90.f),
        _pitch(0.f),
        _speed(glm::radians(1.f)),
        _sensitivity(0.25f),
        _zoom(68.f),
        _worldUp(0.f, 1.f, 0.f)
{}

Kiwi::Engine::Primitive::FPSCamera::FPSCamera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) :
        _position(position),
        _front(glm::vec3(0.f, 0.f, -1.f)),
        _up(up),
        _right(glm::vec3(1.f, 0.f, 0.f)),
        _yaw(yaw),
        _pitch(pitch),
        _speed(glm::radians(1.f)),
        _sensitivity(0.25f),
        _zoom(68.f),
        _worldUp(0.f, 1.f, 0.f)
{}

glm::mat4 Kiwi::Engine::Primitive::FPSCamera::getViewMat4() const {
    return glm::lookAt(_position, _position + _front, _up);
}

void Kiwi::Engine::Primitive::FPSCamera::move(Kiwi::Engine::Primitive::Camera::Action action, float delta) {
    float vel = _speed * delta;
    switch (action) {
        case Action::FORWARD:
            _position += _front * vel;
            break;
        case Action::BACKWARD:
            _position -= _front * vel;
            break;
        case Action::STRAFE_LEFT:
            _position -= _right * vel;
            break;
        case Action::STRAFE_RIGHT:
            _position += _right * vel;
            break;
    }
}

void Kiwi::Engine::Primitive::FPSCamera::center(float xoffset, float yoffset) {
    xoffset *= _sensitivity;
    yoffset *= _sensitivity;

    _yaw += xoffset;
    _pitch += yoffset;
    glm::clamp(_pitch, -89.f, 89.f);
    updateVectors();
}

void Kiwi::Engine::Primitive::FPSCamera::zoom(float y) {
    _zoom -= y;
    _zoom = glm::clamp(_zoom, 20.f, 120.f);
}

void Kiwi::Engine::Primitive::FPSCamera::updateVectors() {
    glm::vec3 front(
            cos(glm::radians(_yaw)) * cos(glm::radians(_pitch)),
            sin(glm::radians(_pitch)),
            sin(glm::radians(_yaw) * cos(glm::radians(_pitch)))
    );

    _front = glm::normalize(front);
    _right = glm::normalize(glm::cross(_front, _worldUp));
    _up = glm::normalize(glm::cross(_right, _front));
}

glm::mat4 Kiwi::Engine::Primitive::FPSCamera::getProjectionMat4() const {
    return glm::perspective(glm::radians(_zoom), 1280.f / 800.f, 0.1f, 1000.f);
}

glm::vec3 Kiwi::Engine::Primitive::FPSCamera::getPosition(void) const {
    return _position;
}

void Kiwi::Engine::Primitive::FPSCamera::setPosition(glm::vec3 position) {
    _position = position;
}
