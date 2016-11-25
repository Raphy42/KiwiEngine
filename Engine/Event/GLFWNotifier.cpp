//
// Created by Raphael DANTZER on 11/25/16.
//

#include "GLFWNotifier.h"

Kiwi::Engine::Event::GLFWNotifier::GLFWNotifier(GLFWwindow *window) : _handle(window) {
//    glfwSetCharCallback(_handle, [](GLFWChar){});
//    glfwSetCharModsCallback(_handle, [](){});
    glfwSetCursorEnterCallback(_handle, [](GLFWwindow *w, int entered) {

    });
    glfwSetCursorPosCallback(_handle, [](GLFWwindow *w, double xpos, double ypos) {

    });
    glfwSetDropCallback(_handle, [](GLFWwindow *w, int count, const char **paths) {

    });
    glfwSetMouseButtonCallback(_handle, [](GLFWwindow *w, int button, int action, int mods) {

    });
//    glfwSetErrorCallback();
    glfwSetFramebufferSizeCallback(_handle, [](GLFWwindow *w, int width, int height) {

    });
}

Kiwi::Engine::Event::GLFWNotifier::~GLFWNotifier() {

}

void Kiwi::Engine::Event::GLFWNotifier::notify(void *data, unsigned long size) {

}

