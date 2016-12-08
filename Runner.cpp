//
// Created by Raphael DANTZER on 12/8/16.
//

#include "Runner.h"
#include "Engine/Event/Type.h"

namespace kEvent = Kiwi::Engine::Event;

void Runner::update(Kiwi::Engine::Event::Type::PlayerEvent &notification) {
    switch (notification.type) {
        case kEvent::Type::PlayerInteraction::MOVE:
            break;
        case kEvent::Type::PlayerInteraction::HIT:
            std::cout << notification.health.damage << std::endl;
            break;
        case kEvent::Type::PlayerInteraction::DEATH:
            std::cout << "U ARE DED" << std::endl;
            break;
        default:
            std::cout << "default" << std::endl;
    }
}

void Runner::update(Kiwi::Engine::Event::Type::GLFWEvent &notification) {
    switch (notification.type) {
        case kEvent::Type::HumanInteraction::KEY_PRESSED:
            switch (notification.key.key) {
                case GLFW_KEY_W:
                    _camera->move(Kiwi::Engine::Primitive::Camera::Action::FORWARD, 3.f);
                    break;
                case GLFW_KEY_A:
                    _camera->move(Kiwi::Engine::Primitive::Camera::Action::STRAFE_LEFT, 10.f);
                    break;
                case GLFW_KEY_D:
                    _camera->move(Kiwi::Engine::Primitive::Camera::Action::STRAFE_RIGHT, 10.f);
                    break;
                default:
                    break;
            }
        case kEvent::Type::HumanInteraction::KEY_RELEASED:
            switch (notification.key.key) {
                default:
                    break;
            }
        default:
            break;
    }
}

Kiwi::Engine::Primitive::FPSCamera * Runner::getCamera() const {
    return _camera;
}

void Runner::setCamera(Kiwi::Engine::Primitive::FPSCamera *camera) {
    _camera = camera;
}

void Runner::setPosition(glm::vec3 pos) {

}

void Runner::gameLoop(void) {
//    _camera->move(Kiwi::Engine::Primitive::FPSCamera::Action::FORWARD, 1.f);
}
