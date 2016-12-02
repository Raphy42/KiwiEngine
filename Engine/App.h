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
#include "../Core/Config.h"
#include "Renderer/Renderer.h"
#include "Assets/Storage.h"

namespace Kiwi {
    namespace Engine {
        class CoreListener : public Event::Listener<Event::Type::CoreEvent> {
        public:
            void update(Event::Type::CoreEvent &notification) override {
                switch (notification.type) {
                    case Event::Type::CoreInteraction::SHADER_LINK_ERROR:
                        std::cerr << "Linker: " << notification.message << std::endl;
                        break;
                    case Event::Type::CoreInteraction::SHADER_BUILD_ERROR:
                        std::cerr << "Shader: " << notification.message << std::endl;
                        break;
                    default:
                        std::cerr << "ERROR: " << notification.message << std::endl;
                }
            }
        };

        class App {
        public:
            App();
            virtual ~App();

            void start();

            void run();

            bool ok() const;

            typedef Event::Dispatcher<Event::Type::GLFWEvent> GLFWDispatcher;
            typedef Event::Dispatcher<Event::Type::CoreEvent> CoreDispatcher;
            typedef Core::Filesystem::VirtualFilesystem VFS;

        private:
            std::unique_ptr<GraphicContextInterface> _graphics;
            std::unique_ptr<VFS> _vfs;
            Core::Config _config;

        protected:
            std::unique_ptr<GLFWDispatcher>     _hid;
            std::unique_ptr<CoreDispatcher>     _core;
            CoreListener _coreListener;
            Renderer::Renderer _renderer;
            Asset::Storage _storage;

            bool _keepOpen;
        };

    }
}

#endif //KIWIENGINE_ENGINE_H
