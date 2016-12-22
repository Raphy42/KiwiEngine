//
// Created by Raphael DANTZER on 12/22/16.
//

#ifndef KIWIENGINE_BSP_H
#define KIWIENGINE_BSP_H

#include <type_traits>

namespace Kiwi {
    namespace Core {
        namespace BSP {
            template<class T>
            class Node {
            public:
                Node() : _value(T()), _left(nullptr), _right(nullptr) {}

                Node(const T &value, Node *left = nullptr, Node *right = nullptr) :
                        _value(value),
                        _left(left),
                        _right(right) {}

                ~Node() = default;

                T getValue() const {
                    return _value;
                }

                void setValue(T value) {
                    Node::_value = value;
                }

                Node *getLeft() const {
                    return _left;
                }

                void setLeft(Node *left) {
                    _left = left;
                }

                Node *getRight() const {
                    return _right;
                }

                void setRight(Node *right) {
                    _right = right;
                }

            protected:
                T _value;
                Node *_left;
                Node *_right;

            };

            template<class T>
            class Btree {
            public:
                Btree() : _root(new Node<T>) {}

                Btree(Node<T> *root) : _root(root) {}

                ~Btree() { destroyLeaf(_root); };

                void insert(const T data) {
                    return insertInLeaf(data, _root);
                }

                Node<T> *search(const T data) {
                    return searchInLeaf(data, _root);
                }

            protected:
                void destroyLeaf(Node<T> *leaf) {
                    if (leaf != nullptr) {
                        destroyLeaf(leaf->getLeft());
                        destroyLeaf(leaf->getRight());
                        delete leaf;
                    }
                }

                void insertInLeaf(const T data, Node<T> *leaf) {
                    if (data < leaf->getValue()) {
                        if (leaf->getLeft() != nullptr)
                            insertInLeaf(data, leaf->getLeft());
                        else
                            leaf->setLeft(new Node<T>(data));
                    } else if (data >= leaf->getValue()) {
                        if (leaf->getRight() != nullptr)
                            insertInLeaf(data, leaf->getRight());
                        else
                            leaf->setRight(new Node<T>(data));
                    }
                }

                Node<T> *searchInLeaf(const T data, Node<T> *leaf) {
                    if (leaf != nullptr) {
                        if (data == leaf->getValue())
                            return leaf;
                        if (data < leaf->getValue())
                            return searchInLeaf(data, leaf->getLeft());
                        else
                            return searchInLeaf(data, leaf->getRight());
                    }
                    else
                        return nullptr;
                }

                Node<T>             *_root;
            };
        }
    }
}

#endif //KIWIENGINE_BSP_H
