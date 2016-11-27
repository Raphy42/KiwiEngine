//
// Created by Raphael DANTZER on 11/27/16.
//

#ifndef KIWIENGINE_CREATOR_H
#define KIWIENGINE_CREATOR_H

#include "Level.h"

namespace Kiwi { namespace Engine { namespace Scene {
            class Creator
            {
            public:
                Creator() {};
                ~Creator() {};

                virtual Level       *createLevelFromConfig(void) = 0;

                Level               *createLevelFromScene(Node *root) const;

            private:
            };
        }
    }
}

#endif //KIWIENGINE_CREATOR_H
