//
// Created by Raphael DANTZER on 11/22/16.
//

#ifndef KIWIENGINE_OPENGLGRAPHICCONTEXT_H
#define KIWIENGINE_OPENGLGRAPHICCONTEXT_H


#include <utility>
#include "GraphicContextInterface.h"

namespace Kiwi { namespace Engine {
        class OpenglGraphicContext : public GraphicContextInterface {
        public:
            OpenglGraphicContext();
            OpenglGraphicContext(std::pair<int, int> size, const char *title);
            OpenglGraphicContext(std::pair<int, int> size, const char *title, std::pair<int, int> version);

        private:
            std::pair<int, int>     _size;

        };
    }
}


#endif //KIWIENGINE_OPENGLGRAPHICCONTEXT_H
