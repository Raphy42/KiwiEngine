//
// Created by Raphael DANTZER on 11/26/16.
//

#ifndef KIWIENGINE_TYPE_H
#define KIWIENGINE_TYPE_H

#include "../../Core/CoreGraphics.h"
#include <string>

namespace Kiwi {
    namespace Engine {
        namespace Event {
            struct Type {
                enum class HumanInteraction : int {
                    NONE = 0x0,
                    WINDOW_MOVED,
                    WINDOW_RESIZED,
                    WINDOW_CLOSED,
                    WINDOW_FOCUSED,
                    WINDOW_DEFOCUSED,
                    WINDOW_ICONIFIED,
                    WINDOW_RESTORED,
                    FRAMEBUFFER_RESIZED,
                    BUTTON_PRESSED,
                    BUTTON_RELEASED,
                    CURSOR_MOVED,
                    CURSOR_ENTERED,
                    CURSOR_LEFT,
                    SCROLLED,
                    KEY_PRESSED,
                    KEY_REPEATED,
                    KEY_RELEASED,
                    CHARACTER_INPUT,
                    FILE_DROPPED
                };

                enum class CoreInteraction : int {
                    NONE = 0x0,
                    CRITICAL,
                    WARNING,
                    INFO
                };

                typedef struct CoreEvent_ {
                    Type::CoreInteraction type;
                    std::string message;
                } CoreEvent;

                typedef struct GLFWEvent_ {
                    Type::HumanInteraction type;
                    GLFWwindow *handle;
                    struct {
                        double x;
                        double y;
                    } pos;
                    struct {
                        int width;
                        int height;
                    } size;
                    struct {
                        int key;
                        int scancode;
                        int mods;
                    } key;
                    struct {
                        int button;
                        int mods;
                    } button;
                    struct {
                        unsigned int codepoint;
                        int mods;
                    } character;
                    struct {
                        int count;
                        const char **paths;
                    } file;
                } GLFWEvent;
            };
        }
    }
}

#endif //KIWIENGINE_TYPE_H
