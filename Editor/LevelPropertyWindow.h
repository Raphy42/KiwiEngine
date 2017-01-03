//
// Created by Raphael DANTZER on 12/16/16.
//

#ifndef KIWIENGINE_LEVELPROPERTYWINDOW_H
#define KIWIENGINE_LEVELPROPERTYWINDOW_H

#include "WindowInterface.h"
#include "../Engine/Scene/Graph.h"

namespace Kiwi {
    namespace Editor {
        class LevelPropertyWindow : public WindowInterface {
        public:
            virtual void render() override;

            void addEntityToSceneDialog() const;
            void showEntityList() const;
            void showEntityDetail(Kiwi::Engine::Scene::GraphData *pData) const;
        };

    }
}


#endif //KIWIENGINE_LEVELPROPERTYWINDOW_H
