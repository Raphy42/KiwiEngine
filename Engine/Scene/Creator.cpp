//
// Created by Raphael DANTZER on 11/27/16.
//

#include "Creator.h"

namespace kE = Kiwi::Engine;

kE::Scene::Level
kE::Scene::Creator::createLevelFromConfig(Kiwi::Core::JSONConfig config) {
    kE::Scene::Level level;

    level.setName(config.get<std::string>("name"));

    return level;
}

