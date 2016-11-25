//
// Created by Raphael DANTZER on 11/25/16.
//

#ifndef KIWIENGINE_CHANNEL_H
#define KIWIENGINE_CHANNEL_H

#include <boost/interprocess/ipc/message_queue.hpp>
#include <iostream>

namespace bip = boost::interprocess;

namespace Kiwi {
    namespace Engine {
        namespace Event {
            template<class T>
            class Channel {
            public:
                Channel(const char *name, unsigned long size) :
                        _queue(bip::create_only, name, size, sizeof(T)) {};

                ~Channel() {};

                bool send(T &data, unsigned int priority) {
                    try {
                        _queue.send(const_cast<void *>(data), sizeof(T), priority);
                    } catch (const bip::interprocess_exception &e) {
                        std::cerr << "BOOST IPC FAILURE: " << e.what() << std::endl;
                        return false;
                    }
                    return true;
                }

            private:
                bip::message_queue _queue;
            };
        }
    }
}

#endif //KIWIENGINE_CHANNEL_H
