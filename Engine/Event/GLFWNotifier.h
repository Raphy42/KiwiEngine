//
// Created by Raphael DANTZER on 11/25/16.
//

#ifndef KIWIENGINE_GLFWEVENTNOTIFIER_H
#define KIWIENGINE_GLFWEVENTNOTIFIER_H

#include <vector>
#include "../../Core/CoreGraphics.h"
#include "Notifier.h"

/**
 * Original derived from gleq/gleq.h by elmindreda @ glfw dot org
 */
namespace Kiwi {
    namespace Engine {
        namespace Event {
            class GLFWNotifier : public Notifier<int> {
            public:
                GLFWNotifier(GLFWwindow *window);

                virtual ~GLFWNotifier();

                void notify(void *data, unsigned long size) override;

                enum class Type : int {
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

                typedef union Event {
                    Type type;
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
                        unsigned int codepoint;
                        int mods;
                    } character;
                    struct {
                        std::vector<const char *> paths;
                    } file;
                } Event_t;

            private:
                GLFWwindow *_handle;
            };
        }
    }
}


#endif //KIWIENGINE_GLFWEVENTNOTIFIER_H
