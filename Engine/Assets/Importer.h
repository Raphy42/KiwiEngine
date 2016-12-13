//
// Created by Raphael DANTZER on 12/13/16.
//

#ifndef KIWIENGINE_IMPORTER_H
#define KIWIENGINE_IMPORTER_H

#include "Asset.h"

namespace Kiwi {
    namespace Engine {
        namespace Asset {

            class Importer {
            public:
                static std::vector<Asset> createAssetsFromFile(const char *filename);

            private:
            };

        }
    }
}


#endif //KIWIENGINE_IMPORTER_H
