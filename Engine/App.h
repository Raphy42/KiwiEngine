//
// Created by Raphael DANTZER on 11/24/16.
//

#ifndef KIWIENGINE_ENGINE_H
#define KIWIENGINE_ENGINE_H

#include <memory>
#include "../Core/Initializable.h"
#include "../Core/Filesystem/VirtualFilesystem.h"

namespace Kiwi {
    namespace Engine {
        class App {
        public:
            App();

            virtual ~App();

            void start() const;

        private:
            std::unique_ptr<Core::Initializable> _graphics;
            std::unique_ptr<Core::Filesystem::VirtualFilesystem> _vfs;
        };

    }
}

#endif //KIWIENGINE_ENGINE_H
