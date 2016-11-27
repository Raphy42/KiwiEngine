//
// Created by Raphaël Dantzer on 26/11/16.
//

#ifndef KIWIENGINE_LEVEL_H
#define KIWIENGINE_LEVEL_H

#include "Node.h"

namespace Kiwi { namespace Engine { namespace Scene {
            class Level {
            public:
                Level() {};
                Level(Node *root) : _root(root) {}
                ~Level() {};

                Node *getScene() const {
                    return _root;
                }

            private:
                Node                *_root;
            };
        }
    }
}


#endif //KIWIENGINE_LEVEL_H
