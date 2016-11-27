//
// Created by Raphael DANTZER on 11/27/16.
//

#include "Creator.h"

namespace kE = Kiwi::Engine;

kE::Scene::Level *
kE::Scene::Creator::createLevelFromScene(kE::Scene::Node *root) const {
    return (new kE::Scene::Level(root));
}

