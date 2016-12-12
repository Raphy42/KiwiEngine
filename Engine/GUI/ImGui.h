#include "../../Core/Graphics.h"
#include "../../vendor/imgui/imgui.h"
#include "../Event/Listener.h"
#include "../Event/Type.h"

#ifndef KIWIENGINE_IMGUI_H
#define KIWIENGINE_IMGUI_H
// ImGui GLFW binding with OpenGL3 + shaders
// In this binding, ImTextureID is used to store an OpenGL 'GLuint' texture identifier. Read the FAQ about ImTextureID in imgui.cpp.

// You can copy and use unmodified imgui_impl_* files in your project. See main.cpp for an example of using this.
// If you use this binding you'll need to call 4 functions: ImGui_ImplXXXX_Init(), ImGui_ImplXXXX_NewFrame(), ImGui::Render() and ImGui_ImplXXXX_Shutdown().
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.
// https://github.com/ocornut/imgui

IMGUI_API bool ImGui_ImplGlfwGL3_Init(GLFWwindow *window, bool install_callbacks);

IMGUI_API void ImGui_ImplGlfwGL3_Shutdown();

IMGUI_API void ImGui_ImplGlfwGL3_NewFrame();

// Use if you want to reset your rendering device without losing ImGui state.
IMGUI_API void ImGui_ImplGlfwGL3_InvalidateDeviceObjects();

IMGUI_API bool ImGui_ImplGlfwGL3_CreateDeviceObjects();

// GLFW callbacks (installed by default if you enable 'install_callbacks' during initialization)
// Provided here if you want to chain callbacks.
// You can also handle inputs yourself and use those as a reference.
IMGUI_API void ImGui_ImplGlfwGL3_MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

IMGUI_API void ImGui_ImplGlfwGL3_ScrollCallback(GLFWwindow *window, double xoffset, double yoffset);

IMGUI_API void ImGui_ImplGlfwGL3_KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

IMGUI_API void ImGui_ImplGlfwGL3_CharCallback(GLFWwindow *window, unsigned int c);


namespace Kiwi {
    namespace Engine {
        namespace GUI {
            class ImGuiListener : public Event::Listener<Event::Type::GLFWEvent> {
            public:
                virtual void update(Event::Type::GLFWEvent &notification) override {
                    switch (notification.type) {
                        case Event::Type::HumanInteraction::BUTTON_PRESSED :
                        case Event::Type::HumanInteraction::BUTTON_RELEASED :
                            ImGui_ImplGlfwGL3_MouseButtonCallback(nullptr, notification.button.button,
                                                                  notification.button.mods, 0);
                            break;
                        case Event::Type::HumanInteraction::KEY_RELEASED :
                            ImGui_ImplGlfwGL3_KeyCallback(nullptr, notification.key.key, notification.key.scancode,
                                                          GLFW_RELEASE, notification.key.mods);
                            break;
                        case Event::Type::HumanInteraction::KEY_PRESSED :
                            ImGui_ImplGlfwGL3_KeyCallback(nullptr, notification.key.key, notification.key.scancode,
                                                          GLFW_PRESS, notification.key.mods);
                            break;
                        case Event::Type::HumanInteraction::KEY_REPEATED :
                            ImGui_ImplGlfwGL3_KeyCallback(nullptr, notification.key.key, notification.key.scancode,
                                                          GLFW_REPEAT, notification.key.mods);
                            break;
                        case Event::Type::HumanInteraction::CHARACTER_INPUT :
                            ImGui_ImplGlfwGL3_CharCallback(nullptr, notification.character.codepoint);
                        default:
                            break;
                    }
                }
            };
        }
    }
}


#endif //KIWIENGINE_IMGUI_H
