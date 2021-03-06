//
// Created by Raphael DANTZER on 11/22/16.
//

#include "OpenglGraphicContext.h"
#include "../Core/Opengl.h"
#include "GUI/ImGui.h"

Kiwi::Engine::OpenglGraphicContext::OpenglGraphicContext() :
    _size(std::pair<int, int>(1280, 800)),
    _title("Default"),
    _version(std::pair<int, int>(4, 1)),
    _windowHints(std::vector<std::pair<int, int>>({
                                                          {GLFW_CONTEXT_VERSION_MAJOR, _version.first},
                                                          {GLFW_CONTEXT_VERSION_MINOR, _version.second},
                                                          {GLFW_OPENGL_FORWARD_COMPAT, true},
                                                          {GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE},
                                                          {GLFW_SAMPLES, 2}
                                                  }))
{

}

Kiwi::Engine::OpenglGraphicContext::OpenglGraphicContext(std::pair<int, int> size, const char *title) :
        _size(size),
        _title(title),
        _version(std::pair<int, int>(4, 1)),
        _windowHints(std::vector<std::pair<int, int>>({
                                                              {GLFW_CONTEXT_VERSION_MAJOR, _version.first},
                                                              {GLFW_CONTEXT_VERSION_MINOR, _version.second},
                                                              {GLFW_OPENGL_FORWARD_COMPAT, true},
                                                              {GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE},
                                                              {GLFW_SAMPLES, 2}
                                                      }))
{
}

Kiwi::Engine::OpenglGraphicContext::OpenglGraphicContext(std::pair<int, int> size, const char *title,
                                                         std::pair<int, int> version) :
        _size(size),
        _title(title),
        _version(version),
        _windowHints(std::vector<std::pair<int, int>>({
                                                              {GLFW_CONTEXT_VERSION_MAJOR, _version.first},
                                                              {GLFW_CONTEXT_VERSION_MINOR, _version.second},
                                                              {GLFW_OPENGL_FORWARD_COMPAT, true},
                                                              {GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE},
                                                              {GLFW_SAMPLES, 2}
                                                      }))
{
}

Kiwi::Engine::OpenglGraphicContext::OpenglGraphicContext(std::pair<int, int> size, const char *title,
                                                         std::pair<int, int> version,
                                                         std::vector<std::pair<int, int>> windowhints) :
        _size(size),
        _title(title),
        _version(version),
        _windowHints(windowhints)
{
}


void Kiwi::Engine::OpenglGraphicContext::PreInit() {
    if (_windowHints.size() == 0)
        throw std::runtime_error("You must set window hints or use default constructor");
    if (!glfwInit())
        throw std::runtime_error("Unable to launch glfw3");
    for (auto const it : _windowHints)
        glfwWindowHint(it.first, it.second);
}

void Kiwi::Engine::OpenglGraphicContext::Init() {
    _window = glfwCreateWindow(_size.first, _size.second, _title, nullptr, nullptr);
    if (_window == nullptr)
        throw std::runtime_error("Failed to create window");
}

void Kiwi::Engine::OpenglGraphicContext::PostInit() {
    glfwGetFramebufferSize(_window, &_framebuffer.first, &_framebuffer.second);
    glfwMakeContextCurrent(_window);
    glViewport(0, 0, _framebuffer.first, _framebuffer.second);
    //bind event notifier
    _notifier = new Event::GLFWNotifier(_window);
    _notifier->start();

#if defined(APPLE_FINALLY_OPENGL_4_3)
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(Core::glDebugOutput, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
#endif
    ImGui_ImplGlfwGL3_Init(_window, false);
}

Kiwi::Engine::OpenglGraphicContext::~OpenglGraphicContext() {
    glfwDestroyWindow(_window);
    glfwTerminate();
}

void Kiwi::Engine::OpenglGraphicContext::Update() {
    glfwPollEvents();
}

void Kiwi::Engine::OpenglGraphicContext::swapBuffers(void) const {
    glfwSwapBuffers(_window);
}

