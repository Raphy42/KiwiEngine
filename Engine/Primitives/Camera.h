//
// Created by Raphaël Dantzer on 26/11/16.
//

#ifndef KIWIENGINE_CAMERA_H
#define KIWIENGINE_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Kiwi {
    namespace Engine {
        namespace Primitive {
            class Camera {
            public:
                virtual ~Camera() {}

                enum class Action {
                    FORWARD,
                    BACKWARD,
                    STRAFE_LEFT,
                    STRAFE_RIGHT
                };

                virtual glm::mat4 getViewMat4() const = 0;

                virtual glm::mat4 getProjectionMat4() const = 0;

                virtual void move(Action action, float delta = 0.5f) = 0;

                virtual void center(float xoffset, float yoffset) = 0;

                virtual void zoom(float y) = 0;

            private:
            };
        }
    }
}

#endif //KIWIENGINE_CAMERA_H
