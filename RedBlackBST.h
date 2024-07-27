#ifndef ALGS4_REDBLACKBST_H
#define ALGS4_REDBLACKBST_H


#include "BST.h"
#include <memory>

template<typename Key, typename Value>
class RedBlackBST : public BST<Key, Value> {
private:
    static constexpr bool RED = true, BLACK = false;
    using BST<Key, Value>::root;
    using BST<Key, Value>::size;

    struct Node : public BST<Key, Value>::Node {
        bool color;  // 由其父结点指向它的链接的颜色

        Node(Key key, Value val, int N, bool color) :
                BST<Key, Value>::Node(key, val, N), color(color) {}
    };

    bool isRed(std::shared_ptr<Node> x) const {
        if (x == nullptr) return false;
        return x->color;
    }

    std::shared_ptr<Node> rotateLeft(std::shared_ptr<Node> h) {
        std::shared_ptr<Node> x = std::dynamic_pointer_cast<Node>(h->right);
        h->right = x->left;
        x->left = h;
        x->color = h->color;
        h->color = RED;
        x->N = h->N;
        h->N = 1 + size(h->left) + size(h->right);
        return x;
    }

    std::shared_ptr<Node> rotateRight(std::shared_ptr<Node> h) {
        std::shared_ptr<Node> x = std::dynamic_pointer_cast<Node>(h->left);
        h->left = x->right;
        x->right = h;
        x->color = h->color;
        h->color = RED;
        x->N = h->N;
        h->N = 1 + size(h->left) + size(h->right);
        return x;
    }

    void flipColors(std::shared_ptr<Node> h) {
        h->color = RED;
        std::dynamic_pointer_cast<Node>(h->left)->color = BLACK;
        std::dynamic_pointer_cast<Node>(h->right)->color = BLACK;
    }

    std::shared_ptr<Node> put(std::shared_ptr<Node> h, const Key &key, const Value &val) {
        if (h == nullptr) return std::make_shared<Node>(key, val, 1, RED);
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

        h->N = size(h->left) + size(h->right) + 1;
        return h;
    }

public:
    void put(const Key &key, const Value &val) override {
        root = put(std::dynamic_pointer_cast<Node>(root), key, val);
        std::dynamic_pointer_cast<Node>(root)->color = BLACK;
    }
};


#endif //ALGS4_REDBLACKBST_H
