//
// Created by Raphael DANTZER on 11/27/16.
//

#ifndef KIWIENGINE_CONFIG_H
#define KIWIENGINE_CONFIG_H

namespace Kiwi { namespace Core { namespace Config {
            template <typename T>
            constexpr T     diffuseTextureId = "texture_diffuse";

            template <typename T>
            constexpr T     specularTextureId = "texture_specular";
    }
}

#endif //KIWIENGINE_CONFIG_H
