#include <iostream>
#include <array>
#include <glm/gtc/type_ptr.hpp>
#include "Engine/App.h"
#include "Engine/Assets/Loader.h"
#include "Engine/Renderer/PhongMaterial.h"
#include "Engine/Renderer/PhongTexturedMaterial.h"
#include "Engine/Renderer/CubeMaterial.h"
#include "Editor/Editor.h"
#include "Editor/Properties.h"
#include "Core/bsp.h"

#define TEST

namespace kE = Kiwi::Engine;

#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))

std::array<const char *, 20> type_str = {
        "NONE",
        "WINDOW_MOVED",
        "WINDOW_RESIZED",
        "WINDOW_CLOSED",
        "WINDOW_FOCUSED",
        "WINDOW_DEFOCUSED",
        "WINDOW_ICONIFIED",
        "WINDOW_RESTORED",
        "FRAMEBUFFER_RESIZED",
        "BUTTON_PRESSED",
        "BUTTON_RELEASED",
        "CURSOR_MOVED",
        "CURSOR_ENTERED",
        "CURSOR_LEFT",
        "SCROLLED",
        "KEY_PRESSED",
        "KEY_REPEATED",
        "KEY_RELEASED",
        "CHARACTER_INPUT",
        "FILE_DROPPED"
};

class UserInputListener : public kE::Event::Listener<kE::Event::Type::GLFWEvent> {
public:
    void update(Kiwi::Engine::Event::Type::GLFWEvent &notification) override {
        static bool wireframe = false;

        switch (notification.type) {
            case kE::Event::Type::HumanInteraction::KEY_PRESSED:
                switch (notification.key.key) {
                    case GLFW_KEY_ESCAPE :
                        exit(EXIT_SUCCESS);
                    default:
                        break;
                }
                break;
            case kE::Event::Type::HumanInteraction::FRAMEBUFFER_RESIZED:
                glViewport(0, 0, notification.size.width, notification.size.height);
            default:
                break;
        }
    }
};

class DebugInputListener : public kE::Event::Listener<kE::Event::Type::GLFWEvent> {
public:
    void update(Kiwi::Engine::Event::Type::GLFWEvent &notification) override {
//        ImGui::Text("Event : %s", type_str[static_cast<int>(notification.type)]);
    }
};

int main(void) {
//    Game *game = new Game();

    Kiwi::Editor::Editor *editor = new Kiwi::Editor::Editor();

    editor->init();

    kE::Asset::Loader loader;

    try {
        while (1)
//            game->loop();
            editor->loop();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    return 0;
}
