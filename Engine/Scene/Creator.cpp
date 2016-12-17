//
// Created by Raphael DANTZER on 11/27/16.
//

#include <glm/gtc/type_ptr.hpp>
#include "Creator.h"

namespace kE = Kiwi::Engine;

kE::Scene::Level
kE::Scene::Creator::createLevelFromConfig(Kiwi::Core::JSONConfig config) {
    Engine::Scene::Level level;
    std::vector<float> tmp;

    level.setName(config.get<std::string>("name"));

    tmp = config.getMatrix<float>("description.transform");
    if (tmp.size())
        level.setTransform(glm::make_mat4(tmp.data()));
    //todo warn user that default world transform was used


    return level;
}

