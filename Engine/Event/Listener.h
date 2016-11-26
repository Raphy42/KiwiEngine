//
// Created by Raphael DANTZER on 11/26/16.
//

#ifndef KIWIENGINE_LISTENER_H
#define KIWIENGINE_LISTENER_H

#include <memory>


namespace Kiwi {
    namespace Engine {
        namespace Event {
            template<class Notification>
            class Listener {
            public:
                Listener() : _state(false) {};

                virtual ~Listener() {};

                virtual void update(Notification &notification) = 0;

                void start(void) { _state = true; };

                void stop(void) { _state = false; };

            private:
                bool _state;
            };
        }
    }
}

#endif //KIWIENGINE_LISTENER_H
