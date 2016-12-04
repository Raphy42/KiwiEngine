//
// Created by Raphaël Dantzer on 04/12/16.
//

#include "PhongTexturedMaterial.h"

Kiwi::Engine::Renderer::PhongTexturedMaterial::PhongTexturedMaterial() {

}

Kiwi::Engine::Renderer::PhongTexturedMaterial::~PhongTexturedMaterial() {

}

void Kiwi::Engine::Renderer::PhongTexturedMaterial::bind(unsigned int slot) {

}

Kiwi::Engine::Renderer::Shading::Type Kiwi::Engine::Renderer::PhongTexturedMaterial::getType() const {
    return Shading::Type::PHONG_TEXTURED;
}

void Kiwi::Engine::Renderer::PhongTexturedMaterial::setParameter(std::string name, glm::vec3 value) {

}

void Kiwi::Engine::Renderer::PhongTexturedMaterial::bindShader(GLProgram shader) {
    _shader = shader;
    GLuint bind = _shader.get();

    _locationMap.emplace("object_color", glGetUniformLocation(bind, "objectColor"));
    _locationMap.emplace("light_color", glGetUniformLocation(bind, "lightColor"));
    _locationMap.emplace("light_pos", glGetUniformLocation(bind, "lightPos"));
}

void Kiwi::Engine::Renderer::PhongTexturedMaterial::addMap(Kiwi::Engine::Renderer::Texture texture) {

}

