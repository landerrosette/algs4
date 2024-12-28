#ifndef ALGS4_REDBLACKBST_H
#define ALGS4_REDBLACKBST_H


#include "BST.h"

template<typename Key, typename Value>
class RedBlackBST : public BST<Key, Value> {
private:
    static constexpr bool RED = true, BLACK = false;

    struct Node : public BST<Key, Value>::Node {
        bool color; // color of link from parent to this node

        Node(const Key &key, const Value &val, int N, bool color) : BST<Key, Value>::Node(key, val, N), color(color) {}
    };

    bool isRed(typename BST<Key, Value>::Node *x) const;

    std::unique_ptr<typename BST<Key, Value>::Node> rotateLeft(std::unique_ptr<typename BST<Key, Value>::Node> &h);

    std::unique_ptr<typename BST<Key, Value>::Node> rotateRight(std::unique_ptr<typename BST<Key, Value>::Node> &h);

    void flipColors(typename BST<Key, Value>::Node *h);

    std::unique_ptr<typename BST<Key, Value>::Node> put(std::unique_ptr<typename BST<Key, Value>::Node> &h,
                                                        const Key &key, const Value &val);

    int height(typename BST<Key, Value>::Node *h) const;

public:
    void put(const Key &key, const Value &val) override;

    int height() const { return height(this->root.get()); }
};

template<typename Key, typename Value>
bool RedBlackBST<Key, Value>::isRed(typename BST<Key, Value>::Node *x) const {
    if (!x) return false;
    return static_cast<Node *>(x)->color == RED;
}

template<typename Key, typename Value>
std::unique_ptr<typename BST<Key, Value>::Node> RedBlackBST<Key, Value>::rotateLeft(
    std::unique_ptr<typename BST<Key, Value>::Node> &h) {
    auto x = std::move(h->right);
    h->right = std::move(x->left);
    static_cast<Node *>(x.get())->color = static_cast<Node *>(h.get())->color;
    static_cast<Node *>(h.get())->color = RED;
    x->N = h->N;
    h->N = this->size(h->left.get()) + this->size(h->right.get()) + 1;
    x->left = std::move(h);
    return x;
}

template<typename Key, typename Value>
std::unique_ptr<typename BST<Key, Value>::Node> RedBlackBST<Key, Value>::rotateRight(
    std::unique_ptr<typename BST<Key, Value>::Node> &h) {
    auto x = std::move(h->left);
    h->left = std::move(x->right);
    static_cast<Node *>(x.get())->color = static_cast<Node *>(h.get())->color;
    static_cast<Node *>(h.get())->color = RED;
    x->N = h->N;
    h->N = this->size(h->left.get()) + this->size(h->right.get()) + 1;
    x->right = std::move(h);
    return x;
}

template<typename Key, typename Value>
void RedBlackBST<Key, Value>::flipColors(typename BST<Key, Value>::Node *h) {
    static_cast<Node *>(h)->color = RED;
    static_cast<Node *>(h->left.get())->color = BLACK;
    static_cast<Node *>(h->right.get())->color = BLACK;
}

template<typename Key, typename Value>
std::unique_ptr<typename BST<Key, Value>::Node> RedBlackBST<Key, Value>::put(
    std::unique_ptr<typename BST<Key, Value>::Node> &h, const Key &key, const Value &val) {
    if (!h) return std::make_unique<Node>(key, val, 1, RED);
    if (key < h->key) h->left = put(h->left, key, val);
    else if (key > h->key) h->right = put(h->right, key, val);
    else h->val = val;

    if (isRed(h->right.get()) && !isRed(h->left.get())) h = rotateLeft(h);
    if (isRed(h->left.get()) && isRed(h->left->left.get())) h = rotateRight(h);
    if (isRed(h->left.get()) && isRed(h->right.get())) flipColors(h.get());

    h->N = this->size(h->left.get()) + this->size(h->right.get()) + 1;
    return std::move(h);
}

template<typename Key, typename Value>
int RedBlackBST<Key, Value>::height(typename BST<Key, Value>::Node *h) const {
    if (!h) return -1;
    return 1 + std::max(height(h->left.get()), height(h->right.get()));
}

template<typename Key, typename Value>
void RedBlackBST<Key, Value>::put(const Key &key, const Value &val) {
    this->root = put(this->root, key, val);
    static_cast<Node *>(this->root.get())->color = BLACK;
}


#endif //ALGS4_REDBLACKBST_H
