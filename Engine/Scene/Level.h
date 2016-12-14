//
// Created by Raphaël Dantzer on 26/11/16.
//

#ifndef KIWIENGINE_LEVEL_H
#define KIWIENGINE_LEVEL_H

#include "Entity.h"
#include "Player.h"
#include <string>

namespace Kiwi { namespace Engine { namespace Scene {
            class Level {
            public:
                Level() {};

                Level(Entity &root) : _root(root), _dirty(true) {}
                ~Level() {};

                Entity getScene() {
                    return _root;
                }

                Entity get_root() const {
                    return _root;
                }

                void set_root(Entity _root) {
                    Level::_root = _root;
                }

                const std::string &get_name() const {
                    return _name;
                }

                void set_name(const std::string &name) {
                    _name = name;
                }

                const glm::mat4 &get_transform() const {
                    return _transform;
                }

                void set_transform(const glm::mat4 &_transform) {
                    Level::_transform = _transform;
                }

                void setSkybox(Entity &skybox) {
                    _skybox = skybox;
                }

                Entity getSkybox(void) {
                    return _skybox;
                }

                const Player &get_player() const {
                    return _player;
                }

                void set_player(const Player &player) {
                    _player = player;
                }

                bool isDirty() const {
                    return _dirty;
                }

                void setDirty(bool dirty) {
                    _dirty = dirty;
                }

            private:
                Entity                              _root;
                Entity                              _skybox;
                Player                              _player;
                std::string                         _name;
                glm::mat4                           _transform;
                bool                                _dirty;
            };
        }
    }
}


#endif //KIWIENGINE_LEVEL_H
