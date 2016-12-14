//
// Created by Raphael DANTZER on 12/14/16.
//

#include <string>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ShadowMap.h"

void Kiwi::Engine::Renderer::ShadowMap::update(glm::vec3 lightPosition) {
    _lightPos = lightPosition;

    _shadowTransforms.clear();
    _shadowTransforms.push_back(_shadowProjection
                                * glm::lookAt(_lightPos, _lightPos
                                                         + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
    _shadowTransforms.push_back(_shadowProjection
                                * glm::lookAt(_lightPos, _lightPos
                                                         + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
    _shadowTransforms.push_back(_shadowProjection
                                * glm::lookAt(_lightPos, _lightPos
                                                         + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
    _shadowTransforms.push_back(_shadowProjection
                                * glm::lookAt(_lightPos, _lightPos
                                                         + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));
    _shadowTransforms.push_back(_shadowProjection
                                * glm::lookAt(_lightPos, _lightPos
                                                         + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)));
    _shadowTransforms.push_back(_shadowProjection
                                * glm::lookAt(_lightPos, _lightPos
                                                         + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));

}

void Kiwi::Engine::Renderer::ShadowMap::bind(GLProgram shader) {
    glViewport(0, 0, _width, _height);
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glClear(GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader.get());

    for (GLuint i = 0; i < 6; ++i)
        glUniformMatrix4fv(glGetUniformLocation(shader.get(), ("shadowMatrices[" + std::to_string(i) + "]").c_str()),
                           1, GL_FALSE, glm::value_ptr(_shadowTransforms[i]));
    glUniform1f(glGetUniformLocation(shader.get(), "far_plane"), _far);
    glUniform3fv(glGetUniformLocation(shader.get(), "lightPos"), 1, glm::value_ptr(_lightPos));
}

Kiwi::Engine::Renderer::ShadowMap::ShadowMap(float width, int height) :
    _width(width),
    _height(height)
{
    _shadowTransforms.reserve(6);
    GLuint depthMapFBO;
    glGenFramebuffers(1, &depthMapFBO);

    GLuint depthCubemap;
    glGenTextures(1, &depthCubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
    for (GLuint i = 0; i < 6; ++i)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, _width, _height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        throw std::runtime_error("Unable to complete framebuffer shadow map");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
