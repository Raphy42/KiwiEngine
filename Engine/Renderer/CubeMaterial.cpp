//
// Created by Raphael DANTZER on 12/4/16.
//

#include "CubeMaterial.h"

void Kiwi::Engine::Renderer::CubeMaterial::bind(unsigned int slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glUniform1i(glGetUniformLocation(_shader.get(), "skybox"), 0);
    _cubemap.bind();
}

Kiwi::Engine::Renderer::Shading::Type Kiwi::Engine::Renderer::CubeMaterial::getType() const {
    return Shading::Type::SKYBOX;
}

void Kiwi::Engine::Renderer::CubeMaterial::setVec3Parameter(std::string name, glm::vec3 value) {

}

void Kiwi::Engine::Renderer::CubeMaterial::setParameter(std::string name, float value) {

}

void Kiwi::Engine::Renderer::CubeMaterial::bindShader(GLProgram shader) {
    _shader = shader;
}

void Kiwi::Engine::Renderer::CubeMaterial::addMap(Kiwi::Engine::Renderer::Texture texture) {
    if (texture.getType() != Texture::Type::CUBE_MAP)
        return;
    _cubemap = texture;
}

void Kiwi::Engine::Renderer::CubeMaterial::setFlag(std::string name, bool value) {

}
