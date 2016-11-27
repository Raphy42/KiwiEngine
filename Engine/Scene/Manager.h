//
// Created by Raphael DANTZER on 11/27/16.
//

#ifndef KIWIENGINE_MANAGER_H
#define KIWIENGINE_MANAGER_H

#include <vector>
#include "Level.h"

namespace Kiwi { namespace Engine { namespace Scene {
            class Manager
            {
            public:
                Manager() {};
                ~Manager() {};

                void        addLevel(Level *level) { _levels.push_back(level); }
                void        setCurrentLevel(unsigned int id) { _currentLevel = _levels.at(id); }
                Level       *getLevel(void) const { return _currentLevel; }

            private:
                Level                       *_currentLevel;
                std::vector<Level *>        _levels;
            };
        }
    }
}

#endif //KIWIENGINE_MANAGER_H
