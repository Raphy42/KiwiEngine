//
// Created by Raphaël Dantzer on 04/12/16.
//

#ifndef KIWIENGINE_UNIFORM_H
#define KIWIENGINE_UNIFORM_H

#include <unordered_map>
#include <string>

namespace Kiwi {
    namespace Engine {
        namespace Renderer {
            template<typename T>
            void update_uniform(int location, T data);
        }
    }
}

#endif //KIWIENGINE_UNIFORM_H
