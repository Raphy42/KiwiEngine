//
// Created by Raphaël Dantzer on 04/12/16.
//

#include "PhongTexturedMaterial.h"

Kiwi::Engine::Renderer::PhongTexturedMaterial::PhongTexturedMaterial() {

}

void Kiwi::Engine::Renderer::PhongTexturedMaterial::bind(unsigned int slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
    _diffuse.bind();

    glActiveTexture(GL_TEXTURE0 + slot + 1);
    _normal.bind();

    glActiveTexture(GL_TEXTURE0 + slot + 2);
    _specular.bind();

    glActiveTexture(GL_TEXTURE0 + slot + 3);
    _alpha.bind();

}

Kiwi::Engine::Renderer::Shading::Type Kiwi::Engine::Renderer::PhongTexturedMaterial::getType() const {
    return Shading::Type::PHONG_TEXTURED;
}

void Kiwi::Engine::Renderer::PhongTexturedMaterial::bindShader(GLProgram shader) {
    _shader = shader;
    GLuint bind = _shader.get();

    _locationMap.emplace("light_pos", glGetUniformLocation(bind, "light.position"));
    _locationMap.emplace("light_color", glGetUniformLocation(bind, "light.color"));
    _locationMap.emplace("light_ambient", glGetUniformLocation(bind, "light.ambient"));
    _locationMap.emplace("light_falloff", glGetUniformLocation(bind, "light.falloff"));
    _locationMap.emplace("light_radius", glGetUniformLocation(bind, "light.radius"));
    _locationMap.emplace("diffuse_map", glGetUniformLocation(bind, "texDiffuse"));
    _locationMap.emplace("specular_map", glGetUniformLocation(bind, "texSpecular"));
    _locationMap.emplace("alpha_map", glGetUniformLocation(bind, "texAlpha"));
    _locationMap.emplace("normal_map", glGetUniformLocation(bind, "texNormal"));
}

void Kiwi::Engine::Renderer::PhongTexturedMaterial::addMap(Kiwi::Engine::Renderer::Texture texture) {
    switch (texture.getType()) {
        case Texture::Type::ALBEDO:
        case Texture::Type::DIFFUSE:
            _diffuse = texture;
            break;
        case Texture::Type::NORMAL:
            _normal = texture;
            break;
        case Texture::Type::SPECULAR:
            _specular = texture;
            break;
        case Texture::Type::ALPHA:
            _alpha = texture;
            break;
        default:
            throw std::invalid_argument("Only diffuse, specular and normal maps accepted");
    }
}

void Kiwi::Engine::Renderer::PhongTexturedMaterial::setParameter(std::string name, float value) {
    glUseProgram(_shader.get());
    glUniform1f(_locationMap[name], value);
}

void Kiwi::Engine::Renderer::PhongTexturedMaterial::setVec3Parameter(std::string name, glm::vec3 value) {
    glUseProgram(_shader.get());
    glUniform3f(_locationMap[name], value.x, value.y, value.z);
}