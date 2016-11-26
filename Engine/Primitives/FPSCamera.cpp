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
        _speed(3.0f),
        _sensitivity(0.25f) {}

Kiwi::Engine::Primitive::FPSCamera::FPSCamera(glm::vec3 position, glm::vec3 up) :
        _position(position),
        _front(glm::vec3(0.f, 0.f, -1.f)),
        _up(up),
        _right(glm::vec3(1.f, 0.f, 0.f)),
        _yaw(-90.f),
        _pitch(0.f),
        _speed(3.0f),
        _sensitivity(0.25f) {}

Kiwi::Engine::Primitive::FPSCamera::FPSCamera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) :
        _position(position),
        _front(glm::vec3(0.f, 0.f, -1.f)),
        _up(up),
        _right(glm::vec3(1.f, 0.f, 0.f)),
        _yaw(yaw),
        _pitch(pitch),
        _speed(3.0f),
        _sensitivity(0.25f) {}

glm::mat4 Kiwi::Engine::Primitive::FPSCamera::getViewMat4() const {
    glm::lookAt(_position, _position + _front, _up);
}

void Kiwi::Engine::Primitive::FPSCamera::move(Kiwi::Engine::Primitive::Camera::Action action, float delta) {
    float vel = _speed * delta;
    switch (action) {
        case Action::FORWARD:
            _position += _front * vel;
            break;
        case Action::BACKWARD:
            break;
            _position -= _front * vel;
        case Action::STRAFE_LEFT:
            break;
            _position -= _right * vel;
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
    updateVectors();
}

void Kiwi::Engine::Primitive::FPSCamera::zoom(float y) {
    if (_zoom >= 1.f && _zoom <= 45.f)
        _zoom -= y;
    _zoom = glm::clamp(_zoom, 1.f, 45.f);
}

void Kiwi::Engine::Primitive::FPSCamera::updateVectors() {
    glm::vec3 front(
            cosf(glm::radians(_yaw)) * cosf(glm::radians(_pitch)),
            sinf(glm::radians(_pitch)),
            sinf(glm::radians(_yaw) * cosf(glm::radians(_pitch)))
    );

    _front = glm::normalize(front);
    _right = glm::normalize(glm::cross(_front, _worldUp));
    _up = glm::normalize(glm::cross(_right, _front));
}

