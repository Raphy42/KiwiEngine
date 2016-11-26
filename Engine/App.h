//
// Created by Raphael DANTZER on 11/24/16.
//

#ifndef KIWIENGINE_ENGINE_H
#define KIWIENGINE_ENGINE_H

#include <memory>
#include "../Core/Initializable.h"
#include "../Core/Filesystem/VirtualFilesystem.h"
#include "GraphicContextInterface.h"
#include "Event/Dispatcher.h"

namespace Kiwi {
    namespace Engine {
        class App {
        public:
            App();
            virtual ~App();

            void start();

            void run() const;

            bool ok() const;

            typedef Event::Dispatcher<Event::Type::GLFWEvent> GLFWDispatcher;
            typedef Event::Dispatcher<Event::Type::CoreEvent> CoreDispatcher;
            typedef Core::Filesystem::VirtualFilesystem VFS;

            std::unique_ptr<GLFWDispatcher> _hid;
            std::unique_ptr<CoreDispatcher> _core;

        private:
            std::unique_ptr<GraphicContextInterface> _graphics;
            std::unique_ptr<VFS> _vfs;
            bool _keepOpen;
        };

    }
}

#endif //KIWIENGINE_ENGINE_H
