//
// Created by Raphael DANTZER on 12/15/16.
//

#ifndef KIWIENGINE_GLOBALEDITORINSTANCE_H
#define KIWIENGINE_GLOBALEDITORINSTANCE_H

#include "../Core/Config.h"
#include "../Core/Filesystem/VirtualFilesystem.h"
#include "../Engine/Scene/Level.h"
#include "../Engine/Scene/Graph.h"
#include "Properties.h"

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

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
                    coreConfig("config/config.ini"),
                    state(State::NONE)
            {
                vfs.bind(coreConfig.get<std::string>("Filesystem.root"));
                vfs.setDirectories({
                                           {"shaders",  coreConfig.get("Filesystem.shaders")},
                                           {"models",   coreConfig.get("Filesystem.models")},
                                           {"textures", coreConfig.get("Filesystem.textures")},
                                           {"levels",   coreConfig.get("Filesystem.levels")}
                                   });
                std::string filename = "config/" + coreConfig.get("Config.editor");
                if (vfs.exists(filename)) {
                    std::ifstream f(filename);
                    {
                        if (f.good()) {
                            boost::archive::xml_iarchive iarchive(f);
                            iarchive >> BOOST_SERIALIZATION_NVP(properties);
                        }
                    }
                }
            };

            ~GlobalInstance() {
                std::string filename = "config/" + coreConfig.get("Config.editor");
                std::ofstream f(filename);
                {
                    if (f.good()) {
                        boost::archive::xml_oarchive oarchive(f);
                        oarchive << BOOST_SERIALIZATION_NVP(properties);
                    }
                }
            }

            Properties                              properties;
            Core::INIConfig                         coreConfig;
            Core::JSONConfig                        levelConfig;
            Core::Filesystem::VirtualFilesystem     vfs;
            State                                   state;
            Kiwi::Engine::Scene::Level              world;
            Kiwi::Engine::Scene::Graph              *graph;

            //Cache
            struct _cache {
                std::vector<Kiwi::Engine::Scene::GraphData *> selection;
            } cache;

            static GlobalInstance &get(void) {
                static GlobalInstance instance; //Todo: you gotta love those side effects
                return instance;
            }

        private:

        };

    }
}


#endif //KIWIENGINE_GLOBALEDITORINSTANCE_H
