//
// Created by Raphael DANTZER on 12/4/16.
//

#include "Material.h"

void Kiwi::Engine::Renderer::Material::bind(unsigned int slot) const {
    for (const auto &texture : _textures)
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        texture.bind();
        ++slot;
    }
}

void Kiwi::Engine::Renderer::Material::addMap(Kiwi::Engine::Renderer::Texture texture) {
    _textures.push_back(texture);
    if (texture.getType() > Renderer::Texture::Type::ALBEDO)
        _type = Type::PBR;
}

Kiwi::Engine::Renderer::Material::Type Kiwi::Engine::Renderer::Material::getType() const {
    return _type;
}
