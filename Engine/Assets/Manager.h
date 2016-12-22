//
// Created by Raphaël Dantzer on 02/12/16.
//

#ifndef KIWIENGINE_MANAGER_H
#define KIWIENGINE_MANAGER_H

#include <unordered_map>
#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/unordered_map.hpp>
#include "Asset.h"

namespace Kiwi {
    namespace Engine {
        namespace Asset {
            class Manager {
            public:
                Manager() = default;
                ~Manager() {};

                typedef std::unordered_map<std::string, Texture>    TextureMap;
                typedef std::unordered_map<std::string, Prop>       PropMap;

            private:
                TextureMap              _textures;
                PropMap                 _models;

                friend boost::serialization::access;

                template <class Archive>
                void serialize(Archive &ar, const unsigned int flags) {
                    ar & boost::serialization::make_nvp("textures", _textures);
                    ar & boost::serialization::make_nvp("models", _models);
                }
            };
        }
    }
}

class Manager {

};


#endif //KIWIENGINE_MANAGER_H
