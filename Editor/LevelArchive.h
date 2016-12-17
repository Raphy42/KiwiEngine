//
// Created by Raphael DANTZER on 12/17/16.
//

#ifndef KIWIENGINE_LEVELARCHIVE_H
#define KIWIENGINE_LEVELARCHIVE_H

#include <boost/serialization/access.hpp>
#include <iostream>
#include "../Engine/Scene/Level.h"

namespace Kiwi {
    namespace Editor {
        class LevelArchive : public Kiwi::Engine::Scene::Level {
        public:
            LevelArchive() : Kiwi::Engine::Scene::Level() {};

        private:
            friend std::ostream &operator<<(std::ostream &os, const LevelArchive &ar);

            friend class boost::serialization::access;

            template<class Archive>
            void serialize(Archive &ar) {
                ar & _name;
                ar & _root;
            }
        };
    }
}


#endif //KIWIENGINE_LEVELARCHIVE_H
