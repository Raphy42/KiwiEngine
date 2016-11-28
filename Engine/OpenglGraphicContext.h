//
// Created by Raphael DANTZER on 11/22/16.
//

#ifndef KIWIENGINE_OPENGLGRAPHICCONTEXT_H
#define KIWIENGINE_OPENGLGRAPHICCONTEXT_H


#include <utility>
#include <vector>
#include "../Core/Graphics.h"
#include "GraphicContextInterface.h"
#include "Event/GLFWNotifier.h"

namespace Kiwi { namespace Engine {
        class OpenglGraphicContext : public GraphicContextInterface {
        public:
            OpenglGraphicContext();
            OpenglGraphicContext(std::pair<int, int> size, const char *title);
            OpenglGraphicContext(std::pair<int, int> size, const char *title, std::pair<int, int> version);
            OpenglGraphicContext(std::pair<int, int> size, const char *title, std::pair<int, int> version, std::vector<std::pair<int, int>> windowhints);

            ~OpenglGraphicContext();

            void PreInit() override;

            void Init() override;

            void PostInit() override;

            void Update() override;

            virtual void swapBuffers(void) const override;

            virtual Event::Notifier<Event::Type::GLFWEvent> *getNotifier() override { return _notifier; };

        private:
            std::pair<int, int>                 _size;
            std::pair<int, int>                 _framebuffer;
            std::pair<int, int>                 _version;
            std::vector<std::pair<int, int>>    _windowHints;

            const char              *_title;

            GLFWwindow              *_window;

            Event::GLFWNotifier *_notifier;
        };
    }
}


#endif //KIWIENGINE_OPENGLGRAPHICCONTEXT_H
