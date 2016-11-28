//
// Created by Raphaël Dantzer on 26/11/16.
//

#ifndef KIWIENGINE_NODE_H
#define KIWIENGINE_NODE_H

#include <vector>
#include <glm/detail/type_mat4x4.hpp>
#include "../Primitives/Mesh.h"
#include "../Renderer/Material.h"

namespace Kiwi {
    namespace Engine {
        namespace Scene {
            class Node {
            public:
                Node() : _material(Renderer::Material::Type::TEST) {};

                Node(Primitive::Mesh mesh, Renderer::Material material) : _mesh(mesh), _material(material) {};
                ~Node() {};

                unsigned int getId(void) const {
                    return _nodeId;
                }

                Node *getParent() const {
                    return _parent;
                }

                void setParent(Node *parent) {
                    _parent = parent;
                }

                const std::vector<Node> getChildren() const {
                    return _children;
                }

                void setChildren(const std::vector<Node> &children) {
                    _children = children;
                }

                void addChild(Node child) {
                    _children.push_back(child);
                }

                void addChildMesh(Primitive::Mesh mesh) {
                    Node node = Node(mesh, Renderer::Material(Renderer::Material::Type::TEST));
                    _children.push_back(node);
                }

                Primitive::Mesh getMesh() const {
                    return _mesh;
                }

                Renderer::Material getMaterial() const {
                    return _material;
                }

                void removeChildrenById(unsigned int id) {
                    std::for_each(_children.begin(), std::vector<Node>::iterator(), [&](Node node) {
                        unsigned int i = 0;

                        if (node.getId() == id)
                            _children.erase(_children.begin() + i);
                            ++i;
                    });
                }

            private:
                Primitive::Mesh _mesh;
                Renderer::Material _material;

                unsigned int            _nodeId;

                Node                    *_parent;
                std::vector<Node> _children;

                glm::mat4               _transform;
            };
        }
    }
}

#endif //KIWIENGINE_NODE_H
