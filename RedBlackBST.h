#ifndef ALGS4_REDBLACKBST_H
#define ALGS4_REDBLACKBST_H


#include "BST.h"
#include <memory>

template<typename Key, typename Value>
class RedBlackBST : public BST<Key, Value> {
private:
    static constexpr bool RED = true, BLACK = false;

    struct Node : public BST<Key, Value>::Node {
        bool color;  // 由其父结点指向它的链接的颜色

        Node(Key key, Value val, int N, bool color) : BST<Key, Value>::Node(key, val, N), color(color) {}
    };

    bool isRed(std::shared_ptr<Node> x) const;

    std::shared_ptr<Node> rotateLeft(std::shared_ptr<Node> h);

    std::shared_ptr<Node> rotateRight(std::shared_ptr<Node> h);

    void flipColors(std::shared_ptr<Node> h);

    std::shared_ptr<Node> put(std::shared_ptr<Node> h, const Key &key, const Value &val);

public:
    void put(const Key &key, const Value &val) override;
};

template<typename Key, typename Value>
bool RedBlackBST<Key, Value>::isRed(std::shared_ptr<Node> x) const {
    if (!x) return false;
    return x->color == RED;
}

template<typename Key, typename Value>
std::shared_ptr<typename RedBlackBST<Key, Value>::Node> RedBlackBST<Key, Value>::rotateLeft(std::shared_ptr<Node> h) {
    std::shared_ptr<Node> x = std::dynamic_pointer_cast<Node>(h->right);
    h->right = x->left;
    x->left = h;
    x->color = h->color;
    h->color = RED;
    x->N = h->N;
    h->N = this->size(h->left) + this->size(h->right) + 1;
    return x;
}

template<typename Key, typename Value>
std::shared_ptr<typename RedBlackBST<Key, Value>::Node> RedBlackBST<Key, Value>::rotateRight(std::shared_ptr<Node> h) {
    std::shared_ptr<Node> x = std::dynamic_pointer_cast<Node>(h->left);
    h->left = x->right;
    x->right = h;
    x->color = h->color;
    h->color = RED;
    x->N = h->N;
    h->N = this->size(h->left) + this->size(h->right) + 1;
    return x;
}

template<typename Key, typename Value>
void RedBlackBST<Key, Value>::flipColors(std::shared_ptr<Node> h) {
    h->color = RED;
    std::dynamic_pointer_cast<Node>(h->left)->color = BLACK;
    std::dynamic_pointer_cast<Node>(h->right)->color = BLACK;
}

template<typename Key, typename Value>
std::shared_ptr<typename RedBlackBST<Key, Value>::Node>
RedBlackBST<Key, Value>::put(std::shared_ptr<Node> h, const Key &key, const Value &val) {
    if (!h) return std::make_shared<Node>(key, val, 1, RED);
    if (key < h->key) h->left = put(std::dynamic_pointer_cast<Node>(h->left), key, val);
    else if (key > h->key) h->right = put(std::dynamic_pointer_cast<Node>(h->right), key, val);
    else h->val = val;

    if (isRed(std::dynamic_pointer_cast<Node>(h->right))
        && !isRed(std::dynamic_pointer_cast<Node>(h->left)))
        h = rotateLeft(h);
    if (isRed(std::dynamic_pointer_cast<Node>(h->left))
        && isRed(std::dynamic_pointer_cast<Node>(h->left->left)))
        h = rotateRight(h);
    if (isRed(std::dynamic_pointer_cast<Node>(h->left))
        && isRed(std::dynamic_pointer_cast<Node>(h->right)))
        flipColors(h);

    h->N = this->size(h->left) + this->size(h->right) + 1;
    return h;
}

template<typename Key, typename Value>
void RedBlackBST<Key, Value>::put(const Key &key, const Value &val) {
    this->root = put(std::dynamic_pointer_cast<Node>(this->root), key, val);
    std::dynamic_pointer_cast<Node>(this->root)->color = BLACK;
}


#endif //ALGS4_REDBLACKBST_H
