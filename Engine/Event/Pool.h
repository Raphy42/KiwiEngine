//
// Created by Raphael DANTZER on 11/24/16.
//

#ifndef KIWIENGINE_POOL_H
#define KIWIENGINE_POOL_H

#include <boost/circular_buffer.hpp>
#include "Notification.h"

namespace Kiwi {
    namespace Engine {
        namespace Event {
            class Pool {
            public:
                Pool() : _notifs(512) {};

                ~Pool() {};

                typedef boost::circular_buffer<Notification> NotificationPool;

                void enqueue(Notification notification);

                void erase();

                unsigned long size() const;

                const NotificationPool &get_notifs() const;

            private:
                NotificationPool _notifs;
            };
        }
    }
}


#endif //KIWIENGINE_POOL_H
