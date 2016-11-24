//
// Created by Raphael DANTZER on 11/24/16.
//

#ifndef KIWIENGINE_LISTENER_H
#define KIWIENGINE_LISTENER_H

#include "Notification.h"

namespace Kiwi {
    namespace Engine {
        namespace Event {
            class Listener {
            public:
                virtual ~Listener() = 0;

                virtual void handle(Notification notification) = 0;
            };
        }
    }
}

#endif //KIWIENGINE_LISTENER_H
