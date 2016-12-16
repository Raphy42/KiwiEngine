//
// Created by Raphaël Dantzer on 02/12/16.
//

#ifndef KIWIENGINE_MANAGER_H
#define KIWIENGINE_MANAGER_H

#include "../../Core/Filesystem/VirtualFilesystem.h"
#include "../../Core/INIConfig.h"
#include "Storage.h"

namespace Kiwi {
    namespace Engine {
        namespace Asset {
            class Manager {
            public:
                Manager();

                ~Manager() {};

            private:
                Storage _storage;
                Core::Filesystem::VirtualFilesystem _vfs;
                Core::INIConfig _config;
            };
        }
    }
}

class Manager {

};


#endif //KIWIENGINE_MANAGER_H
