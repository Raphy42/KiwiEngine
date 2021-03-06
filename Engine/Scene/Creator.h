//
// Created by Raphael DANTZER on 11/27/16.
//

#ifndef KIWIENGINE_CREATOR_H
#define KIWIENGINE_CREATOR_H

#include "Level.h"
#include "../../Core/Config.h"

namespace Kiwi { namespace Engine { namespace Scene {
            class Creator
            {
            public:
                Creator() {};
                ~Creator() {};

                Level               *createLevelFromConfig(Core::JSONConfig config);
                Level               *createLevelFromScene(Entity *root) const;

            private:
            };
        }
    }
}

#endif //KIWIENGINE_CREATOR_H
