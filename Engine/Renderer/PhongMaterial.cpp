//
// Created by Raphaël Dantzer on 04/12/16.
//

#include "PhongMaterial.h"

Kiwi::Engine::Renderer::PhongMaterial::PhongMaterial() :
        _dirty(true),
        _color(glm::vec3(1.f, 1.f, 1.f)),
        _shader(0) {}


void Kiwi::Engine::Renderer::PhongMaterial::setColor(glm::vec3 color) {
    _color = color;
    _dirty = true;
}

void Kiwi::Engine::Renderer::PhongMaterial::bindShader(GLProgram shader) {
    _shader = shader;
    GLuint bind = _shader.get();

    _locationMap.emplace("object_color", glGetUniformLocation(bind, "objectColor"));
    _locationMap.emplace("light_color", glGetUniformLocation(bind, "lightColor"));
    _locationMap.emplace("light_pos", glGetUniformLocation(bind, "lightPos"));
    _locationMap.emplace("view_pos", glGetUniformLocation(bind, "viewPos"));
}

void Kiwi::Engine::Renderer::PhongMaterial::bindTextures(unsigned int slot) {
    if (_dirty)
        update();
}

void Kiwi::Engine::Renderer::PhongMaterial::setParameter(std::string name, glm::vec3 value) {
    glUseProgram(_shader.get());
    glUniform3f(_locationMap[name], value.x, value.y, value.z);
}

Kiwi::Engine::Renderer::Shading::Type Kiwi::Engine::Renderer::PhongMaterial::getType() const {
    return Shading::Type::PHONG;
}

void Kiwi::Engine::Renderer::PhongMaterial::addMap(Kiwi::Engine::Renderer::Texture texture) {
    throw std::runtime_error("You need phong_material_texture (not implemented)");
}

void Kiwi::Engine::Renderer::PhongMaterial::update() {
    GLuint bind = _shader.get();
    glUniform3f(_locationMap["object_color"], _color.x, _color.y, _color.z);
}
