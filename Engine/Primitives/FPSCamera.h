//
// Created by Raphaël Dantzer on 26/11/16.
//

#ifndef KIWIENGINE_FPSCAMERA_H
#define KIWIENGINE_FPSCAMERA_H

#include "Camera.h"

namespace Kiwi {
    namespace Engine {
        namespace Primitive {
            class FPSCamera : public Camera {
            public:
                FPSCamera();

                FPSCamera(glm::vec3 position, glm::vec3 up);

                FPSCamera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);

                virtual glm::mat4 getViewMat4() const override;

                virtual void move(Action action, float delta) override;

                virtual void center(float xoffset, float yoffset) override;

                virtual void zoom(float y) override;

            private:
                glm::vec3 _position;
                glm::vec3 _front;
                glm::vec3 _up;

                glm::vec3 _right;
                glm::vec3 _worldUp;

                float _yaw;
                float _pitch;

                float _speed;
                float _sensitivity;
                float _zoom;

                void updateVectors();
            };
        }
    }
}

#endif //KIWIENGINE_FPSCAMERA_H
