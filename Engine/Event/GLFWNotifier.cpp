//
// Created by Raphael DANTZER on 11/25/16.
//

#include <iostream>
#include "GLFWNotifier.h"
#include "Type.h"

Kiwi::Engine::Event::GLFWNotifier::GLFWNotifier(GLFWwindow *window) :
        _handle(window) {
    //bindTextures Notifier to window
    glfwSetWindowUserPointer(_handle, this);
}

Kiwi::Engine::Event::GLFWNotifier::~GLFWNotifier() {

}

inline static Kiwi::Engine::Event::GLFWNotifier *
getNotifier(GLFWwindow *window) {
    return static_cast<Kiwi::Engine::Event::GLFWNotifier *>(glfwGetWindowUserPointer(window));
}

void Kiwi::Engine::Event::GLFWNotifier::start(void) {
//    glfwSetCharCallback(_handle, [](GLFWChar){});
//    glfwSetCharModsCallback(_handle, [](){});

    glfwSetCursorEnterCallback(_handle, [](GLFWwindow *w, int entered) {
        Type::GLFWEvent event;

        event.handle = w;
        if (entered)
            event.type = Type::HumanInteraction::CURSOR_ENTERED;
        else
            event.type = Type::HumanInteraction::CURSOR_LEFT;
        getNotifier(w)->notify(event);
    });

    glfwSetCursorPosCallback(_handle, [](GLFWwindow *w, double xpos, double ypos) {
        Type::GLFWEvent event;

        event.handle = w;
        event.type = Type::HumanInteraction::CURSOR_MOVED;
        event.pos.x = xpos;
        event.pos.y = ypos;
        getNotifier(w)->notify(event);
    });

    glfwSetDropCallback(_handle, [](GLFWwindow *w, int count, const char **paths) {
        Type::GLFWEvent event;

        event.handle = w;
        event.type = Type::HumanInteraction::FILE_DROPPED;
//        event.file.paths.reserve(static_cast<unsigned long>(count));
//        for (int i = 0; i < count; ++i)
//            event.file.paths.push_back(paths[i]);
        getNotifier(w)->notify(event);
    });

    glfwSetMouseButtonCallback(_handle, [](GLFWwindow *w, int button, int action, int mods) {
        Type::GLFWEvent event;

        event.handle = w;
        if (action == GLFW_PRESS)
            event.type = Type::HumanInteraction::BUTTON_PRESSED;
        else if (action == GLFW_RELEASE)
            event.type = Type::HumanInteraction::BUTTON_RELEASED;
        event.button.button = button;
        event.button.mods = mods;
        getNotifier(w)->notify(event);
    });
//    glfwSetErrorCallback();
    glfwSetFramebufferSizeCallback(_handle, [](GLFWwindow *w, int width, int height) {
        Type::GLFWEvent event;

        event.handle = w;
        event.type = Type::HumanInteraction::FRAMEBUFFER_RESIZED;
        event.size.width = width;
        event.size.height = height;
        getNotifier(w)->notify(event);
    });

    glfwSetScrollCallback(_handle, [](GLFWwindow *w, double x, double y) {
        Type::GLFWEvent event;

        event.handle = w;
        event.type = Type::HumanInteraction::SCROLLED;
        event.pos.x = x;
        event.pos.y = y;
        getNotifier(w)->notify(event);
    });

    glfwSetKeyCallback(_handle, [](GLFWwindow *w, int key, int scancode, int action, int mods) {
        Type::GLFWEvent event;

        event.handle = w;
        if (action == GLFW_PRESS)
            event.type = Type::HumanInteraction::KEY_PRESSED;
        else if (action == GLFW_RELEASE)
            event.type = Type::HumanInteraction::KEY_RELEASED;
        else if (action == GLFW_REPEAT)
            event.type = Type::HumanInteraction::KEY_REPEATED;
        event.key.key = key;
        event.key.scancode = scancode;
        event.key.mods = mods;
        getNotifier(w)->notify(event);
    });
}

void Kiwi::Engine::Event::GLFWNotifier::notify(Kiwi::Engine::Event::Type::GLFWEvent &notification) {
    _dispatcher->update(notification);
}

void Kiwi::Engine::Event::GLFWNotifier::bind(Kiwi::Engine::Event::Dispatcher<Type::GLFWEvent> *dispatcher) {
    _dispatcher = dispatcher;
}

void Kiwi::Engine::Event::GLFWNotifier::unbind(void) {
    _dispatcher = nullptr;
}


