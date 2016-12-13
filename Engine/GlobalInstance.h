//
// Created by Raphael DANTZER on 12/13/16.
//

#ifndef KIWIENGINE_GLOBALINSTANCE_H
#define KIWIENGINE_GLOBALINSTANCE_H

#include "../Core/Filesystem/VirtualFilesystem.h"

namespace Kiwi {
    namespace Engine {
        static struct GlobalInstance {
            Core::Filesystem::VirtualFilesystem VFS;
        } g_globalInstance;
    }
}

#endif //KIWIENGINE_GLOBALINSTANCE_H
