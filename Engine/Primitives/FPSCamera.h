//
// Created by Raphaël Dantzer on 26/11/16.
//

#ifndef KIWIENGINE_FPSCAMERA_H
#define KIWIENGINE_FPSCAMERA_H

#include <iostream>
#include "Camera.h"
#include "../Event/Listener.h"
#include "../Event/Type.h"

namespace Kiwi {
    namespace Engine {
        namespace Primitive {
            class FPSCamera : public Camera {
            public:
                FPSCamera();

                FPSCamera(glm::vec3 position, glm::vec3 up);

                FPSCamera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);

                virtual glm::mat4 getViewMat4() const override;

                virtual glm::mat4 getProjectionMat4() const override;

                virtual void move(Action action, float delta) override;

                virtual void center(float xoffset, float yoffset) override;

                virtual void zoom(float y) override;

                glm::vec3 getPosition(void) const;

                void setPosition(glm::vec3 position);

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

                void                    updateVectors();
            };

            /**
             * Control camera with the GLFWEvent bus
             * TODO: reformat event system and more abstraction of the event bus
             */
            class FPSCameraEventListener : public Event::Listener<Event::Type::GLFWEvent> {
            public:
                FPSCameraEventListener(FPSCamera *camera) : _camera(camera) {};

                virtual void update(Event::Type::GLFWEvent &notification) override {
                    static float lastX, lastY;
                    float xpos;
                    float ypos;
                    static bool updateMouse = true;

                    static float lastFrame;
                    GLfloat currentFrame = glfwGetTime();
                    static float deltaTime = currentFrame - lastFrame;
                    lastFrame = currentFrame;

                    switch (notification.type) {
                        case Event::Type::HumanInteraction::CURSOR_ENTERED:
                            _in = true;
                            break;
                        case Event::Type::HumanInteraction::CURSOR_LEFT:
                            _in = false;
                            break;
                        case Event::Type::HumanInteraction::CURSOR_MOVED :
                            xpos = static_cast<float>(notification.pos.x);
                            ypos = static_cast<float>(notification.pos.y);

                            if (_first)

                            {
                                lastX = xpos;
                                lastY = ypos;
                                _first = false;
                            }
                            if (_in && updateMouse)
                                _camera->center(xpos - lastX, lastY - ypos);
                            lastX = xpos;
                            lastY = ypos;
                            break ;
                        case Event::Type::HumanInteraction::SCROLLED :
                            _camera->zoom(static_cast<float>(notification.pos.y));
                            break;
                        case Event::Type::HumanInteraction::KEY_PRESSED :
                        case Event::Type::HumanInteraction::KEY_REPEATED :
                            switch (notification.key.key) {
                                case GLFW_KEY_W:
                                    _camera->move(Camera::Action::FORWARD, deltaTime);
                                    break;
                                case GLFW_KEY_S:
                                    _camera->move(Camera::Action::BACKWARD, deltaTime);
                                    break;
                                case GLFW_KEY_A:
                                    _camera->move(Camera::Action::STRAFE_LEFT, deltaTime);
                                    break;
                                case GLFW_KEY_D:
                                    _camera->move(Camera::Action::STRAFE_RIGHT, deltaTime);
                                    break;
                                case GLFW_KEY_SPACE:
                                    updateMouse = !updateMouse;
                                    break;
                                default:
                                    break;
                            }
                            break ;
                        default:
                            break ;
                    }
                }

            private:
                FPSCamera      *_camera;
                bool            _first = true;
                bool            _in = false;
            };
        }
    }
}

#endif //KIWIENGINE_FPSCAMERA_H
