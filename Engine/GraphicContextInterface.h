//
// Created by Raphael DANTZER on 11/22/16.
//

#ifndef KIWIENGINE_GRAPHICCONTEXTINTERFACE_H
#define KIWIENGINE_GRAPHICCONTEXTINTERFACE_H

#include "../Core/Initializable.h"

namespace Kiwi { namespace Engine {
        class GraphicContextInterface : public Core::Initializable {
        public:
            virtual ~GraphicContextInterface() = 0;

            enum class Type {
                OPENGL,
                OPENGL_OPENCL,
                VULKAN
            };

        private:
        };
    }
}


#endif //KIWIENGINE_GRAPHICCONTEXTINTERFACE_H
