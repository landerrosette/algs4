#ifndef ALGS4_REDBLACKBST_H
#define ALGS4_REDBLACKBST_H


#include "BST.h"
#include <algorithm>
#include <cassert>

template<typename Key, typename Value>
class RedBlackBST : public BST<Key, Value> {
private:
    static constexpr bool RED = true, BLACK = false;

    struct Node : public BST<Key, Value>::Node {
        bool color; // color of link from parent to this node

        Node(const Key &key, const Value &val, int N, bool color) : BST<Key, Value>::Node(key, val, N), color(color) {}
    };

    bool isRed(const typename BST<Key, Value>::Node *x) const;

    // Make a right-leaning link lean to the left.
    std::unique_ptr<typename BST<Key, Value>::Node> rotateLeft(std::unique_ptr<typename BST<Key, Value>::Node> &h);

    // Make a left-leaning link lean to the right.
    std::unique_ptr<typename BST<Key, Value>::Node> rotateRight(std::unique_ptr<typename BST<Key, Value>::Node> &h);

    // Flip the colors of a node and its two children.
    void flipColors(typename BST<Key, Value>::Node *h);

    // Assuming that h is red and both h.left and h.left.left are black, make h.left or one of its children red.
    std::unique_ptr<typename BST<Key, Value>::Node> moveRedLeft(std::unique_ptr<typename BST<Key, Value>::Node> &h);

    // Assuming that h is red and both h.right and h.right.left are black, make h.right or one of its children red.
    std::unique_ptr<typename BST<Key, Value>::Node> moveRedRight(std::unique_ptr<typename BST<Key, Value>::Node> &h);

    // Restore red-black tree invariant.
    std::unique_ptr<typename BST<Key, Value>::Node> balance(std::unique_ptr<typename BST<Key, Value>::Node> &h);

    std::unique_ptr<typename BST<Key, Value>::Node> put(std::unique_ptr<typename BST<Key, Value>::Node> &h,
                                                        const Key &key, const Value &val);

    std::unique_ptr<typename BST<Key, Value>::Node> remove(std::unique_ptr<typename BST<Key, Value>::Node> &h,
                                                           const Key &key);

    std::unique_ptr<typename BST<Key, Value>::Node> removeMin(std::unique_ptr<typename BST<Key, Value>::Node> &h);

    std::unique_ptr<typename BST<Key, Value>::Node> removeMax(std::unique_ptr<typename BST<Key, Value>::Node> &h);

    int height(const typename BST<Key, Value>::Node *x) const;

    bool is23(const typename BST<Key, Value>::Node *x) const;

    // Does the tree have no red right links, and at most one (left) red links in a row on any path?
    bool is23() const { return is23(this->root.get()); }

    // Does every path from the root to a leaf have the given number of black links?
    bool isBalanced(const typename BST<Key, Value>::Node *x, int black) const;

    // Do all paths from root to leaf have same number of black edges?
    bool isBalanced() const;

public:
    void put(const Key &key, const Value &val) override;

    void remove(const Key &key) override;

    void removeMin() override;

    void removeMax() override;

    int height() const { return height(this->root.get()); }
};

template<typename Key, typename Value>
bool RedBlackBST<Key, Value>::isRed(const typename BST<Key, Value>::Node *x) const {
    if (!x) return false;
    return static_cast<const Node *>(x)->color == RED;
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
    static_cast<Node *>(h)->color = !static_cast<Node *>(h)->color;
    static_cast<Node *>(h->left.get())->color = !static_cast<Node *>(h->left.get())->color;
    static_cast<Node *>(h->right.get())->color = !static_cast<Node *>(h->right.get())->color;
}

template<typename Key, typename Value>
std::unique_ptr<typename BST<Key, Value>::Node> RedBlackBST<Key, Value>::moveRedLeft(
    std::unique_ptr<typename BST<Key, Value>::Node> &h) {
    flipColors(h.get());
    if (isRed(h->right->left.get())) {
        h->right = rotateRight(h->right);
        h = rotateLeft(h);
        flipColors(h.get());
    }
    return std::move(h);
}

template<typename Key, typename Value>
std::unique_ptr<typename BST<Key, Value>::Node> RedBlackBST<Key, Value>::moveRedRight(
    std::unique_ptr<typename BST<Key, Value>::Node> &h) {
    flipColors(h.get());
    if (isRed(h->left->left.get())) {
        h = rotateRight(h);
        flipColors(h.get());
    }
    return std::move(h);
}

template<typename Key, typename Value>
std::unique_ptr<typename BST<Key, Value>::Node> RedBlackBST<Key, Value>::balance(
    std::unique_ptr<typename BST<Key, Value>::Node> &h) {
    if (isRed(h->right.get()) && !isRed(h->left.get())) h = rotateLeft(h);
    if (isRed(h->left.get()) && isRed(h->left->left.get())) h = rotateRight(h);
    if (isRed(h->left.get()) && isRed(h->right.get())) flipColors(h.get());
    h->N = this->size(h->left.get()) + this->size(h->right.get()) + 1;
    return std::move(h);
}

template<typename Key, typename Value>
std::unique_ptr<typename BST<Key, Value>::Node> RedBlackBST<Key, Value>::put(
    std::unique_ptr<typename BST<Key, Value>::Node> &h, const Key &key, const Value &val) {
    if (!h) return std::make_unique<Node>(key, val, 1, RED);
    if (key < h->key) h->left = put(h->left, key, val);
    else if (key > h->key) h->right = put(h->right, key, val);
    else h->val = val;
    return balance(h);
}

template<typename Key, typename Value>
std::unique_ptr<typename BST<Key, Value>::Node> RedBlackBST<Key, Value>::remove(
    std::unique_ptr<typename BST<Key, Value>::Node> &h, const Key &key) {
    if (!h) return nullptr;
    if (key < h->key) {
        if (!isRed(h->left.get()) && !isRed(h->left->left.get())) h = moveRedLeft(h);
        h->left = remove(h->left, key);
    } else {
        if (isRed(h->left.get())) h = rotateRight(h);
        if (key == h->key && !h->right) return nullptr;
        if (!isRed(h->right.get()) && !isRed(h->right->left.get())) h = moveRedRight(h);
        if (key == h->key) {
            auto x = this->min(h->right.get());
            h->key = x->key;
            h->val = x->val;
            h->right = removeMin(h->right);
        } else h->right = remove(h->right, key);
    }
    return balance(h);
}

template<typename Key, typename Value>
std::unique_ptr<typename BST<Key, Value>::Node> RedBlackBST<Key, Value>::removeMin(
    std::unique_ptr<typename BST<Key, Value>::Node> &h) {
    if (!h || !h->left) return nullptr;
    if (!isRed(h->left.get()) && !isRed(h->left->left.get())) h = moveRedLeft(h);
    h->left = removeMin(h->left);
    return balance(h);
}

template<typename Key, typename Value>
std::unique_ptr<typename BST<Key, Value>::Node> RedBlackBST<Key, Value>::removeMax(
    std::unique_ptr<typename BST<Key, Value>::Node> &h) {
    if (!h) return nullptr;
    if (isRed(h->left.get())) h = rotateRight(h);
    if (!h->right) return nullptr;
    if (!isRed(h->right.get()) && !isRed(h->right->left.get())) h = moveRedRight(h);
    h->right = removeMax(h->right);
    return balance(h);
}

template<typename Key, typename Value>
int RedBlackBST<Key, Value>::height(const typename BST<Key, Value>::Node *x) const {
    if (!x) return -1;
    return 1 + std::max(height(x->left.get()), height(x->right.get()));
}

template<typename Key, typename Value>
bool RedBlackBST<Key, Value>::is23(const typename BST<Key, Value>::Node *x) const {
    if (!x) return true;
    if (isRed(x->right.get())) return false;
    if (x != this->root.get() && isRed(x) && isRed(x->left.get())) return false;
    return is23(x->left.get()) && is23(x->right.get());
}

template<typename Key, typename Value>
bool RedBlackBST<Key, Value>::isBalanced(const typename BST<Key, Value>::Node *x, int black) const {
    if (!x) return black == 0;
    if (!isRed(x)) black--;
    return isBalanced(x->left.get(), black) && isBalanced(x->right.get(), black);
}

template<typename Key, typename Value>
bool RedBlackBST<Key, Value>::isBalanced() const {
    int black = 0; // number of black links on path from root to min
    for (auto *x = this->root.get(); x; x = x->left.get())
        if (!isRed(x)) black++;
    return isBalanced(this->root.get(), black);
}

template<typename Key, typename Value>
void RedBlackBST<Key, Value>::put(const Key &key, const Value &val) {
    this->root = put(this->root, key, val);
    static_cast<Node *>(this->root.get())->color = BLACK;
    assert(is23());
    assert(isBalanced());
}

template<typename Key, typename Value>
void RedBlackBST<Key, Value>::remove(const Key &key) {
    if (!isRed(this->root->left.get()) && !isRed(this->root->right.get()))
        static_cast<Node *>(this->root.get())->color = RED;
    this->root = remove(this->root, key);
    if (this->root) static_cast<Node *>(this->root.get())->color = BLACK;
    assert(is23());
    assert(isBalanced());
}

template<typename Key, typename Value>
void RedBlackBST<Key, Value>::removeMin() {
    if (!isRed(this->root->left.get()) && !isRed(this->root->right.get()))
        static_cast<Node *>(this->root.get())->color = RED;
    this->root = removeMin(this->root);
    if (this->root) static_cast<Node *>(this->root.get())->color = BLACK;
    assert(is23());
    assert(isBalanced());
}

template<typename Key, typename Value>
void RedBlackBST<Key, Value>::removeMax() {
    if (!isRed(this->root->left.get()) && !isRed(this->root->right.get()))
        static_cast<Node *>(this->root.get())->color = RED;
    this->root = removeMax(this->root);
    if (this->root) static_cast<Node *>(this->root.get())->color = BLACK;
    assert(is23());
    assert(isBalanced());
}

#endif //ALGS4_REDBLACKBST_H
