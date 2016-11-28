//
// Created by Raphael DANTZER on 11/25/16.
//

#ifndef KIWIENGINE_GLFWEVENTNOTIFIER_H
#define KIWIENGINE_GLFWEVENTNOTIFIER_H

#include "../../Core/Graphics.h"
#include "Notifier.h"
#include "Type.h"

/**
 * Concept (enum and union) taken from gleq/gleq.h by elmindreda @ glfw dot org
 */
namespace Kiwi {
    namespace Engine {
        namespace Event {
            class GLFWNotifier : public Notifier<Type::GLFWEvent> {
            public:
                GLFWNotifier() {};
                GLFWNotifier(GLFWwindow *window);
                virtual ~GLFWNotifier();

                virtual void notify(Type::GLFWEvent &notification) override;

                virtual void bind(Dispatcher<Type::GLFWEvent> *dispatcher) override;

                virtual void unbind(void) override;


                void start(void);
            private:

                GLFWwindow *_handle;
                Dispatcher<Type::GLFWEvent> *_dispatcher;

            };
        }
    }
}


#endif //KIWIENGINE_GLFWEVENTNOTIFIER_H
