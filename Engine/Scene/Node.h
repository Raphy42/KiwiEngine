//
// Created by Raphaël Dantzer on 26/11/16.
//

#ifndef KIWIENGINE_NODE_H
#define KIWIENGINE_NODE_H

#include <vector>
#include <glm/detail/type_mat4x4.hpp>

namespace Kiwi {
    namespace Engine {
        namespace Scene {
            class Node {
            public:
                Node() {};
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

                const std::vector<Node *> &getChildren() const {
                    return _children;
                }

                void setChildren(const std::vector<Node *> &children) {
                    _children = children;
                }

                void addChild(Node *child) {
                    _children.push_back(child);
                }

                void removeChildrenById(unsigned int id) {
                    std::for_each(_children.begin(), std::vector<Node *>::iterator(), [&](Node *node){
                        unsigned int i = 0;

                        if (node->getId() == id)
                            _children.erase(_children.begin() + i);
                            ++i;
                    });
                }

            private:
                unsigned int            _nodeId;
                unsigned int            _meshId;
                unsigned int            _materialId;

                Node                    *_parent;
                std::vector<Node *>     _children;

                glm::mat4               _transform;
            };
        }
    }
}

#endif //KIWIENGINE_NODE_H
