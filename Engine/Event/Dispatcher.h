//
// Created by Raphael DANTZER on 11/25/16.
//

#ifndef KIWIENGINE_SYSTEM_H
#define KIWIENGINE_SYSTEM_H

#include <vector>
#include "Type.h"
#include "Listener.h"

namespace Kiwi {
    namespace Engine {
        namespace Event {
            template<class Notification>
            class Dispatcher {
            public:
                Dispatcher() {};

                virtual ~Dispatcher() {};

                void update(Notification &notification) {
                    for (auto it : _listeners)
                        it->update(notification);

                }

                void bind(Listener<Notification> *listener) {
                    _listeners.push_back(listener);
                }

            private:
                std::vector<Listener<Notification> *> _listeners;
            };
        }
    }
}

#endif //KIWIENGINE_SYSTEM_H
