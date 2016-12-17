//
// Created by Raphael DANTZER on 12/15/16.
//

#ifndef KIWIENGINE_GLOBALEDITORINSTANCE_H
#define KIWIENGINE_GLOBALEDITORINSTANCE_H

#include "../Core/Config.h"
#include "../Core/Filesystem/VirtualFilesystem.h"
#include "../Engine/Scene/Level.h"

namespace Kiwi {
    namespace Editor {

        enum class State : int {
            NONE = 0x0,
            SCENE_OPENED,
            SCENE_LOADED,
            SCENE_MODIFIED,
            SCENE_SAVED
        };

        class GlobalInstance {
        public:
            GlobalInstance() :
                    editorConfig("config/editor.json"),
                    coreConfig("config/config.ini"),
                    state(State::NONE)
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
            Core::INIConfig                         coreConfig;
            Core::JSONConfig                        levelConfig;
            Core::Filesystem::VirtualFilesystem     vfs;
            State                                   state;
            Kiwi::Engine::Scene::Level              world;

            static GlobalInstance &get(void) {
                static GlobalInstance instance; //Todo: you gotta love those side effects
                return instance;
            }

        private:

        };

    }
}


#endif //KIWIENGINE_GLOBALEDITORINSTANCE_H
