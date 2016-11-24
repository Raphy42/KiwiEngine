//
// Created by Raphael DANTZER on 11/24/16.
//

#ifndef KIWIENGINE_NOTIFICATION_H
#define KIWIENGINE_NOTIFICATION_H

#include <string>

namespace Kiwi {
    namespace Engine {
        namespace Event {
            class Notification {
            public:
                virtual ~Notification() = 0;

                virtual enum class Type;

                virtual const std::string getMessage(void) const = 0;

                virtual const Type getType(void) const = 0;

                virtual const int getSender(void) const = 0;

                virtual const int getChannel(void) const = 0;

            private:
            };
        }
    }
}


#endif //KIWIENGINE_NOTIFICATION_H
