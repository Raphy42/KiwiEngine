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

            void addEntityToSceneDialog();
            void showEntityList();
            void showEntityDetail(Kiwi::Engine::Scene::GraphData *pData) const;

        private:
             std::vector<Kiwi::Engine::Scene::Graph *> _cache;
        };

    }
}


#endif //KIWIENGINE_LEVELPROPERTYWINDOW_H
