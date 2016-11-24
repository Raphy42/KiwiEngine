//
// Created by Raphael DANTZER on 11/24/16.
//

#ifndef KIWIENGINE_NOTIFIER_H
#define KIWIENGINE_NOTIFIER_H

#include "Notification.h"

namespace Kiwi {
    namespace Engine {
        namespace Event {
            class Notifier {
            public:
                virtual ~Notifier() = 0;

                virtual void notify() const = 0;

            private:

            };
        }
    }
}


#endif //KIWIENGINE_NOTIFIER_H
