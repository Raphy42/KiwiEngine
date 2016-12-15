//
// Created by Raphael DANTZER on 12/15/16.
//

#ifndef KIWIENGINE_GLOBALINSTANCE_H
#define KIWIENGINE_GLOBALINSTANCE_H

#include "../Core/Config.h"
#include "../Core/Filesystem/VirtualFilesystem.h"

namespace Kiwi {
    namespace Editor {
        static struct GlobalInstance {
            GlobalInstance() :
                    editorConfig("config/editor.json"),
                    coreConfig("config/config.ini")
            {
                vfs.bind(coreConfig.get<std::string>("Filesystem.root"));
                vfs.setDirectories({
                                           {"shaders",  coreConfig.get<std::string>("Filesystem.shaders")},
                                           {"models",   coreConfig.get<std::string>("Filesystem.models")},
                                           {"textures", coreConfig.get<std::string>("Filesystem.textures")},
                                           {"levels",   coreConfig.get<std::string>("Filesystem.levels")}
                                   });
            };

            Core::JSONConfig                        editorConfig;
            Core::Config                            coreConfig;
            Core::Filesystem::VirtualFilesystem     vfs;
        } g_globalInstance;
    }
}


#endif //KIWIENGINE_GLOBALINSTANCE_H
