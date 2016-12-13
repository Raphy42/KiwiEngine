//
// Created by Raphaël Dantzer on 26/11/16.
//

#ifndef KIWIENGINE_NODE_H
#define KIWIENGINE_NODE_H

#include <vector>
#include <glm/detail/type_mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Primitives/Mesh.h"
#include "../Renderer/Material.h"
#include "Actuator.h"

namespace Kiwi {
    namespace Engine {
        namespace Scene {
            class Entity {
            public:
                enum class Type : int {
                    MODEL,
                    MESH,

                };

                Entity() : _material(nullptr) {};

                Entity(Primitive::Mesh mesh, Renderer::Material *material) :
                        _mesh(mesh),
                        _material(material),
                        _transform(glm::mat4())
                {};

                Entity(Primitive::Mesh mesh, Renderer::Material *material, glm::vec3 position) :
                    _mesh(mesh),
                    _material(material),
                    _transform(glm::translate(glm::mat4(), position))
                {};

                ~Entity() {};

                const std::vector<Entity> getChildren() const {
                    return _children;
                }

                void setChildren(const std::vector<Entity> &children) {
                    _children = children;
                }

                void addChild(Entity child) {
                    _children.push_back(child);
                }

                Primitive::Mesh getMesh() const {
                    return _mesh;
                }

                Renderer::Material *getMaterial() const {
                    return _material;
                }

                void setMaterial(Renderer::Material *material) {
                    _material = material;
                }

                glm::mat4 getWorldPos() const {
                    if (_actuator == nullptr)
                        return _transform;
                    else
                        return _actuator->update();
                }

                void setTransform(glm::mat4 transform) {
                    _transform = transform;
                }

                void bindActuator(Actuator *actuator) {
                    _actuator = actuator;
                    setTransform(actuator->update());
                    for (auto &child : _children)
                        child.bindActuator(actuator);
                }

            private:
                Primitive::Mesh         _mesh;
                Renderer::Material      *_material;
                std::vector<Entity>     _children;
                glm::mat4               _transform;
                Actuator                *_actuator = nullptr;
            };
        }
    }
}

#endif //KIWIENGINE_NODE_H
