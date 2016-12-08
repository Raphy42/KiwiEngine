//
// Created by Raphael DANTZER on 12/8/16.
//

#ifndef KIWIENGINE_PLAYER_H
#define KIWIENGINE_PLAYER_H

#include "Actuator.h"
#include "../Primitives/AABB.h"
#include "../Primitives/Camera.h"
#include "../Primitives/FPSCamera.h"
#include "Entity.h"

namespace Kiwi {
    namespace Engine {
        namespace Scene {

            class Player : public Event::Listener<Event::Type::PlayerEvent>, public Event::Listener<Event::Type::GLFWEvent>
            {
            public:
                virtual ~Player() {};

                virtual void update(Event::Type::PlayerEvent &notification) override {};
                virtual void update(Event::Type::GLFWEvent &notification) override {};

                virtual void setPosition(glm::vec3 pos) {};
            };
        }
    }
}


#endif //KIWIENGINE_PLAYER_H
