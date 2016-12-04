//
// Created by Raphaël Dantzer on 26/11/16.
//

#ifndef KIWIENGINE_LEVEL_H
#define KIWIENGINE_LEVEL_H

#include "Entity.h"
#include <string>

namespace Kiwi { namespace Engine { namespace Scene {
            class Level {
            public:
                Level() {};

                Level(Entity &root) : _root(root) {}
                ~Level() {};

                Entity getScene() {
                    return _root;
                }

                Entity get_root() const {
                    return _root;
                }

                void set_root(Entity _root) {
                    Level::_root = _root;
                }

                const std::string &get_name() const {
                    return _name;
                }

                void set_name(const std::string &name) {
                    _name = name;
                }

                const glm::mat4 &get_transform() const {
                    return _transform;
                }

                void set_transform(const glm::mat4 &_transform) {
                    Level::_transform = _transform;
                }

            private:
                Entity _root;
                std::string                         _name;
                glm::mat4                           _transform;
            };
        }
    }
}


#endif //KIWIENGINE_LEVEL_H
