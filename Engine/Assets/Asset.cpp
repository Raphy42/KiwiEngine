//
// Created by Raphael DANTZER on 12/13/16.
//

#include "Asset.h"

namespace Kiwi {
    namespace Engine {
        namespace Asset {
            void Prop::load(const unsigned int flags) {

            }

            Asset::Type Prop::getType(void) const {
                return Type::PROP;
            }

            void World::load(const unsigned int flags) {

            }

            Asset::Type World::getType(void) const {
                return Type::WORLD;
            }

            void Texture::load(const unsigned int flags) {

            }

            Asset::Type Texture::getType(void) const {
                return Type::TEXTURE;
            }
        }
    }
}

