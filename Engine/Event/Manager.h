//
// Created by Raphael DANTZER on 11/24/16.
//

#ifndef KIWIENGINE_MANAGER_H
#define KIWIENGINE_MANAGER_H

#include <vector>
#include "Pool.h"
#include "Notifier.h"
#include "Listener.h"

namespace Kiwi {
    namespace Engine {
        namespace Event {
            class Manager {
            public:
                Manager();

                ~Manager();

                void update(void) const;

                void registerNotifier(Notifier notifier, int channel);

                void registerListener(Listener listener, int channel);

            private:
                std::vector<std::vector<Notifier>> _notifiers;
                std::vector<Listener> _listeners;
                std::vector<Pool> _pools;
            };
        }
    }
}


#endif //KIWIENGINE_MANAGER_H
