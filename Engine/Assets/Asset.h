//
// Created by Raphael DANTZER on 12/13/16.
//

#ifndef KIWIENGINE_ASSET_H
#define KIWIENGINE_ASSET_H

#include <string>
#include "../Primitives/Mesh.h"
#include "../Renderer/Material.h"
#include "../Primitives/AABB.h"

namespace Kiwi {
    namespace Engine {
        namespace Asset {
            class Asset {
            public:
                enum class Type : int {
                    WORLD,
                    PROP,
                    TEXTURE,
                };

                Asset() = default;

                virtual void load(const unsigned int flags) = 0;
                virtual Type getType(void) const = 0;

            protected:
                std::string         _filename;
                std::string         _name;

                friend boost::serialization::access;

                template<class Archive>
                void serialize(Archive &ar, const unsigned int flags) {
                    ar & BOOST_SERIALIZATION_NVP(_filename);
                    ar & BOOST_SERIALIZATION_NVP(_name);
                }

            };

            class World : public Asset {
            public:
                virtual void load(const unsigned int flags) override;

                virtual Type getType(void) const override;
            };

            class Prop : public Asset {
            public:
                virtual void load(const unsigned int flags) override;

                virtual Type getType(void) const override;
            };

            class Texture : public Asset {
            public:
                virtual void load(const unsigned int flags) override;

                virtual Type getType(void) const override;
            };
        }
    }
}

#endif //KIWIENGINE_ASSET_H
