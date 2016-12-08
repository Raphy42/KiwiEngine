//
// Created by Raphael DANTZER on 12/8/16.
//

#ifndef KIWIENGINE_RUNNER_H
#define KIWIENGINE_RUNNER_H

#include "Engine/Scene/Player.h"

class Runner : public Kiwi::Engine::Scene::Player {
public:
    Runner() {};

    virtual void update(Kiwi::Engine::Event::Type::PlayerEvent &notification) override;

    virtual void update(Kiwi::Engine::Event::Type::GLFWEvent &notification) override;

    Kiwi::Engine::Primitive::FPSCamera *getCamera() const;

    void setCamera(Kiwi::Engine::Primitive::FPSCamera *camera);

    virtual void setPosition(glm::vec3 pos) override;

    void gameLoop();

private:
    Kiwi::Engine::Primitive::FPSCamera *_camera;
};

#endif //KIWIENGINE_RUNNER_H
