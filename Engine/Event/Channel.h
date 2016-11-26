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
                        _queue(bip::create_only, name, size, sizeof(T)),
                        _name(name) {}

                ~Channel() {};

                bool send(T *data, unsigned int priority) {
                    try {
                        _queue.send(static_cast<void *>(data), sizeof(T), priority);
                    } catch (const bip::interprocess_exception &e) {
                        std::cerr << "BOOST IPC FAILURE: " << e.what() << std::endl;
                        return false;
                    }
                    return true;
                }

                T receive(void) {
                    T buffer;
                    try {
                        unsigned int priority;
                        bip::message_queue::size_type receved_size;
                        _queue.receive(&buffer, sizeof(T), receved_size, priority);
                        if (receved_size != sizeof(T))
                            return T();
                    } catch (const bip::interprocess_exception &e) {
                        std::cerr << " Unable to read message_queue " << e.what() << std::endl;
                        return T();
                    }
                    return buffer;
                }

            private:
                Channel() = delete;

                bip::message_queue _queue;
                const char *_name;
            };
        }
    }
}

#endif //KIWIENGINE_CHANNEL_H
