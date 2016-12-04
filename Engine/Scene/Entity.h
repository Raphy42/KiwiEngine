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

namespace Kiwi {
    namespace Engine {
        namespace Scene {
            class Entity {
            public:
                Entity() : _material(Renderer::Material::Type::TEST) {};

                Entity(Primitive::Mesh mesh, Renderer::Material material) :
                        _mesh(mesh),
                        _material(material),
                        _transform(glm::mat4())
                {};

                Entity(Primitive::Mesh mesh, Renderer::Material material, glm::vec3 position) :
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

                void addChildMesh(Primitive::Mesh mesh, Renderer::Material material = Renderer::Material(Renderer::Material::Type::TEST)) {
                    Entity node = Entity(mesh, material);
                    _children.push_back(node);
                }

                Primitive::Mesh getMesh() const {
                    return _mesh;
                }

                Renderer::Material getMaterial() const {
                    return _material;
                }

                void setMaterial(const Renderer::Material &material) {
                    _material = material;
                }

                glm::mat4 getWorldPos() const {
                    return _transform;
                }

            private:
                Primitive::Mesh         _mesh;
                Renderer::Material      _material;
                std::vector<Entity>       _children;
                glm::mat4               _transform;
            };
        }
    }
}

#endif //KIWIENGINE_NODE_H
