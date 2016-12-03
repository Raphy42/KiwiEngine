//
// Created by Raphaël Dantzer on 26/11/16.
//

#ifndef KIWIENGINE_LEVEL_H
#define KIWIENGINE_LEVEL_H

#include "Node.h"
#include <string>

namespace Kiwi { namespace Engine { namespace Scene {
            class Level {
            public:
                Level() {};
                Level(Node *root) : _root(root) {}
                ~Level() {};

                Node *getScene() {
                    return _root;
                }

                Node *get_root() const {
                    return _root;
                }

                void set_root(Node *_root) {
                    Level::_root = _root;
                }

                const std::string &get_name() const {
                    return _name;
                }

                void set_name(const std::string &_name) {
                    Level::_name = _name;
                }

                const glm::mat4 &get_transform() const {
                    return _transform;
                }

                void set_transform(const glm::mat4 &_transform) {
                    Level::_transform = _transform;
                }

            private:
                Node                                *_root;
                std::string                         _name;
                glm::mat4                           _transform;
            };
        }
    }
}


#endif //KIWIENGINE_LEVEL_H
