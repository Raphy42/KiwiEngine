#include <iostream>
#include <array>
#include "Engine/App.h"
#include "Engine/Event/Type.h"
#include "Engine/Event/Listener.h"
#include "Engine/Event/Dispatcher.h"
#include "Engine/Event/GLFWNotifier.h"

namespace kE = Kiwi::Engine;

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
        switch (notification.type) {
            case kE::Event::Type::HumanInteraction::KEY_PRESSED:
                switch (notification.key.key) {
                    case GLFW_KEY_ESCAPE :
                        exit(EXIT_SUCCESS);
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
};

class DebugInputListener : public kE::Event::Listener<kE::Event::Type::GLFWEvent> {
    void update(Kiwi::Engine::Event::Type::GLFWEvent &notification) override {
        std::cout << type_str[static_cast<int>(notification.type)] << std::endl;
    }
};


class Game : public kE::App
{
public:
    Game() {}

    void loop(void) {
        start();

        UserInputListener dummyListener;
        DebugInputListener debugListener;

        _hid->bind(&debugListener);
        _hid->bind(&dummyListener);

        while (1) {
            run();
        }
    }
};

int main(void) {
    Game game;

    game.loop();
    return 0;
}