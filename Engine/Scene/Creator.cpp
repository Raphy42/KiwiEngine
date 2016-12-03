//
// Created by Raphael DANTZER on 11/27/16.
//

#include "Creator.h"

namespace kE = Kiwi::Engine;

kE::Scene::Level *
kE::Scene::Creator::createLevelFromScene(kE::Scene::Node *root) const {
    return (new kE::Scene::Level(root));
}

Kiwi::Engine::Scene::Level *Kiwi::Engine::Scene::Creator::createLevelFromConfig(Kiwi::Core::JSONConfig config) {
    kE::Scene::Level *level = new kE::Scene::Level(new kE::Scene::Node);

    level->set_name(config.get<std::string>("name"));
    std::vector<float> transform = config.getVector<float>("transform");

    if (!transform.size())
        level->set_transform(glm::mat4());
    else
        level->set_transform(glm::mat4(transform[0]));

    return level;
}

