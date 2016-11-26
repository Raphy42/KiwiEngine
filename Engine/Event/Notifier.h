//
// Created by Raphael DANTZER on 11/25/16.
//

#ifndef KIWIENGINE_NOTIFIER_H
#define KIWIENGINE_NOTIFIER_H

#include <memory>
#include "Dispatcher.h"

namespace Kiwi {
    namespace Engine {
        namespace Event {
            template<class Notification>
            class Notifier {
            public:
                Notifier() {};

                virtual ~Notifier() {};

                virtual void notify(Notification &notification) = 0;

                virtual void bind(Dispatcher<Notification> *dispatcher) = 0;

                virtual void unbind(void) = 0;

            private:
                std::weak_ptr<Dispatcher<Notification>> _dispatcher;
            };

        }
    }
}

#endif //KIWIENGINE_NOTIFIER_H
