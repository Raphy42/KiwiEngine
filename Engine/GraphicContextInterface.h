//
// Created by Raphael DANTZER on 11/22/16.
//

#ifndef KIWIENGINE_GRAPHICCONTEXTINTERFACE_H
#define KIWIENGINE_GRAPHICCONTEXTINTERFACE_H

#include "../Core/Initializable.h"
#include "Event/Type.h"
#include "Event/Notifier.h"

namespace Kiwi { namespace Engine {
        class GraphicContextInterface : public Core::Initializable {
        public:
            virtual ~GraphicContextInterface() {};

            enum class Type {
                OPENGL,
                OPENGL_OPENCL,
                VULKAN
            };

            virtual void Render() = 0;

            virtual void Clear() = 0;

            virtual Event::Notifier<Event::Type::GLFWEvent> *getNotifier() = 0;

        private:
        };
    }
}


#endif //KIWIENGINE_GRAPHICCONTEXTINTERFACE_H
