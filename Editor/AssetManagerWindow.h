//
// Created by Raphael DANTZER on 1/3/17.
//

#ifndef KIWIENGINE_ASSETMANAGERWINDOW_H
#define KIWIENGINE_ASSETMANAGERWINDOW_H

#include "WindowInterface.h"
#include "../Engine/Renderer/Texture.h"
#include "../Engine/Primitives/Mesh.h"
#include "../Engine/Renderer/Material.h"

namespace Kiwi {
    namespace Editor {
        class AssetManagerWindow : public WindowInterface {
        public:
            virtual void render() override;

        private:

        };
    }
}


#endif //KIWIENGINE_ASSETMANAGERWINDOW_H
