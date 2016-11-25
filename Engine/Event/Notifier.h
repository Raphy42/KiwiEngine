//
// Created by Raphael DANTZER on 11/25/16.
//

#ifndef KIWIENGINE_NOTIFIER_H
#define KIWIENGINE_NOTIFIER_H

#include "Channel.h"

namespace Kiwi {
    namespace Engine {
        namespace Event {
            template<class T>
            class Notifier {
            public:
                virtual ~Notifier() = 0;

                virtual void notify(void *data, unsigned long size) = 0;
            private:
                Channel<T> _channel;
            };
        }
    }
}

#endif //KIWIENGINE_NOTIFIER_H
