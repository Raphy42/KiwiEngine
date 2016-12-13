//
// Created by Raphael DANTZER on 12/13/16.
//

#include "Asset.h"

Kiwi::Engine::Asset::Asset::Asset(std::string &name, Kiwi::Engine::Asset::Asset::Type &type) :
        _name(name),
        _type(type) {}

Kiwi::Engine::Asset::Asset::Asset(std::string &name, Kiwi::Engine::Asset::Asset::Type &type,
                                  std::shared_ptr<Kiwi::Engine::Primitive::Mesh> mesh,
                                  std::shared_ptr<Kiwi::Engine::Renderer::Material> material) :
        _name(name),
        _type(type),
        _mesh(mesh),
        _material(material) {}


Kiwi::Engine::Asset::Asset::Type
Kiwi::Engine::Asset::Asset::getType(void) const {
    return _type;
}


Kiwi::Engine::Primitive::AABB
Kiwi::Engine::Asset::Asset::getBounds(void) const {
    return Kiwi::Engine::Primitive::AABB();
}

void
Kiwi::Engine::Asset::Asset::setBounds(Kiwi::Engine::Primitive::AABB &bounds) {
    _bounds = bounds;
}

