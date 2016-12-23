//
// Created by Raphael DANTZER on 12/15/16.
//

#ifndef KIWIENGINE_WINDOWINTERFACE_H
#define KIWIENGINE_WINDOWINTERFACE_H

#include <unordered_map>
#include <string>

namespace Kiwi {
    namespace Editor {
        class WindowInterface {
        public:
            virtual ~WindowInterface() {};

            virtual void        render() = 0;

        protected:
            std::unordered_map<std::string, bool>   _flags;
        };
    }
}

#endif //KIWIENGINE_WINDOWINTERFACE_H
