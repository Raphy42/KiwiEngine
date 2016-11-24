//
// Created by Raphaël Dantzer on 23/11/16.
//

#ifndef KIWIENGINE_CAMERAINTERFACE_H
#define KIWIENGINE_CAMERAINTERFACE_H

#include <memory>

class CameraInterface {
public:
    virtual void track(std::shared_ptr<int> target) = 0;

    template <typename T>
    virtual void    setFrustum(T width, T height, T near, T far) = 0;

    template <typename T>
    virtual T       getViewMatrix() = 0;
};

#endif //KIWIENGINE_CAMERAINTERFACE_H
