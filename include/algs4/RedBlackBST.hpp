#ifndef ALGS4_REDBLACKBST_HPP
#define ALGS4_REDBLACKBST_HPP


#include <algorithm>
#include <cassert>

#include "BSTBase.hpp"

namespace algs4 {
    namespace internal {
        template<std::totally_ordered Key, typename Value>
        struct RedBlackBSTNode : public BSTNodeBase<Key, Value, RedBlackBSTNode<Key, Value> > {
            bool color;

            RedBlackBSTNode(const Key &key, const Value &val, std::ptrdiff_t N, bool color)
                : BSTNodeBase<Key, Value, RedBlackBSTNode>(key, val, N),
                  color(color) {}
        };
    }

    template<std::totally_ordered Key, typename Value>
    class RedBlackBST : public BSTBase<Key, Value, internal::RedBlackBSTNode<Key, Value> > {
    private:
        using Node = internal::RedBlackBSTNode<Key, Value>;
        static constexpr bool RED = true, BLACK = false;

        bool isRed(const Node *h) const;
        std::unique_ptr<Node> rotateLeft(std::unique_ptr<Node> &h);  // Make a right-leaning link lean to the left.
        std::unique_ptr<Node> rotateRight(std::unique_ptr<Node> &h); // Make a left-leaning link lean to the right.
        void flipColors(Node *h);                                    // Flip the colors of a node and its two children.

        // Assuming that h is red and both h->left and h->left->left are black, make h->left or one of its children red.
        std::unique_ptr<Node> moveRedLeft(std::unique_ptr<Node> &h);
        // Assuming that h is red and both h->right and h->right->left are black, make h->right or one of its children red.
        std::unique_ptr<Node> moveRedRight(std::unique_ptr<Node> &h);
        std::unique_ptr<Node> balance(std::unique_ptr<Node> &h); // Restore red-black tree invariant.
        std::unique_ptr<Node> put(std::unique_ptr<Node> &h, const Key &key, const Value &val);
        std::unique_ptr<Node> remove(std::unique_ptr<Node> &h, const Key &key);
        std::unique_ptr<Node> removeMin(std::unique_ptr<Node> &h);
        std::unique_ptr<Node> removeMax(std::unique_ptr<Node> &h);
        int height(const Node *h) const;
        bool is23(const Node *h) const;
        // Does the tree have no red right links, and at most one (left) red links in a row on any path?
        bool is23() const { return is23(this->root.get()); }
        // Does every path from the root to a leaf have the given number of black links?
        bool isBalanced(const Node *h, int black) const;
        bool isBalanced() const; // Do all paths from root to leaf have same number of black edges?

    public:
        void put(const Key &key, const Value &val) override;
        void remove(const Key &key) override;
        void removeMin() override;
        void removeMax() override;
        int height() const { return height(this->root.get()); }
    };
}

template<std::totally_ordered Key, typename Value>
bool algs4::RedBlackBST<Key, Value>::isRed(const Node *h) const {
    if (!h) return false;
    return h->color == RED;
}

template<std::totally_ordered Key, typename Value>
auto algs4::RedBlackBST<Key, Value>::rotateLeft(std::unique_ptr<Node> &h) -> std::unique_ptr<Node> {
    auto x = std::move(h->right);
    h->right = std::move(x->left);
    x->color = h->color;
    h->color = RED;
    x->N = h->N;
    h->N = this->size(h->left.get()) + this->size(h->right.get()) + 1;
    x->left = std::move(h);
    return x;
}

template<std::totally_ordered Key, typename Value>
auto algs4::RedBlackBST<Key, Value>::rotateRight(std::unique_ptr<Node> &h) -> std::unique_ptr<Node> {
    auto x = std::move(h->left);
    h->left = std::move(x->right);
    x->color = h->color;
    h->color = RED;
    x->N = h->N;
    h->N = this->size(h->left.get()) + this->size(h->right.get()) + 1;
    x->right = std::move(h);
    return x;
}

template<std::totally_ordered Key, typename Value>
void algs4::RedBlackBST<Key, Value>::flipColors(Node *h) {
    h->color = !h->color;
    h->left->color = !h->left->color;
    h->right->color = !h->right->color;
}

template<std::totally_ordered Key, typename Value>
auto algs4::RedBlackBST<Key, Value>::moveRedLeft(std::unique_ptr<Node> &h) -> std::unique_ptr<Node> {
    flipColors(h.get());
    if (isRed(h->right->left.get())) {
        h->right = rotateRight(h->right);
        h = rotateLeft(h);
        flipColors(h.get());
    }
    return std::move(h);
}

template<std::totally_ordered Key, typename Value>
auto algs4::RedBlackBST<Key, Value>::moveRedRight(std::unique_ptr<Node> &h) -> std::unique_ptr<Node> {
    flipColors(h.get());
    if (isRed(h->left->left.get())) {
        h = rotateRight(h);
        flipColors(h.get());
    }
    return std::move(h);
}

template<std::totally_ordered Key, typename Value>
auto algs4::RedBlackBST<Key, Value>::balance(std::unique_ptr<Node> &h) -> std::unique_ptr<Node> {
    if (isRed(h->right.get()) && !isRed(h->left.get())) h = rotateLeft(h);
    if (isRed(h->left.get()) && isRed(h->left->left.get())) h = rotateRight(h);
    if (isRed(h->left.get()) && isRed(h->right.get())) flipColors(h.get());
    h->N = this->size(h->left.get()) + this->size(h->right.get()) + 1;
    return std::move(h);
}

template<std::totally_ordered Key, typename Value>
auto algs4::RedBlackBST<Key, Value>::put(std::unique_ptr<Node> &h, const Key &key,
                                         const Value &val) -> std::unique_ptr<Node> {
    if (!h) return std::make_unique<Node>(key, val, 1, RED);
    if (key < h->key) h->left = put(h->left, key, val);
    else if (key > h->key) h->right = put(h->right, key, val);
    else h->val = val;
    return balance(h);
}

template<std::totally_ordered Key, typename Value>
auto algs4::RedBlackBST<Key, Value>::remove(std::unique_ptr<Node> &h, const Key &key) -> std::unique_ptr<Node> {
    if (!h) return nullptr;
    if (key < h->key) {
        if (!isRed(h->left.get()) && !isRed(h->left->left.get()))
            h = moveRedLeft(h);
        h->left = remove(h->left, key);
    } else {
        if (isRed(h->left.get()))
            h = rotateRight(h);
        if (key == h->key && !h->right)
            return nullptr;
        if (!isRed(h->right.get()) && !isRed(h->right->left.get()))
            h = moveRedRight(h);
        if (key == h->key) {
            const Node *x = this->min(h->right.get());
            h->key = x->key;
            h->val = x->val;
            h->right = removeMin(h->right);
        } else h->right = remove(h->right, key);
    }
    return balance(h);
}

template<std::totally_ordered Key, typename Value>
auto algs4::RedBlackBST<Key, Value>::removeMin(std::unique_ptr<Node> &h) -> std::unique_ptr<Node> {
    if (!h) return nullptr;
    if (!h->left)
        return nullptr;
    if (!isRed(h->left.get()) && !isRed(h->left->left.get()))
        h = moveRedLeft(h);
    h->left = removeMin(h->left);
    return balance(h);
}

template<std::totally_ordered Key, typename Value>
auto algs4::RedBlackBST<Key, Value>::removeMax(std::unique_ptr<Node> &h) -> std::unique_ptr<Node> {
    if (!h) return nullptr;
    if (isRed(h->left.get()))
        h = rotateRight(h);
    if (!h->right)
        return nullptr;
    if (!isRed(h->right.get()) && !isRed(h->right->left.get()))
        h = moveRedRight(h);
    h->right = removeMax(h->right);
    return balance(h);
}

template<std::totally_ordered Key, typename Value>
int algs4::RedBlackBST<Key, Value>::height(const Node *h) const {
    if (!h) return -1;
    return 1 + std::max(height(h->left.get()), height(h->right.get()));
}

template<std::totally_ordered Key, typename Value>
bool algs4::RedBlackBST<Key, Value>::is23(const Node *h) const {
    if (!h) return true;
    if (isRed(h->right.get()))
        return false;
    if (h != this->root.get() && isRed(h) && isRed(h->left.get()))
        return false;
    return is23(h->left.get()) && is23(h->right.get());
}

template<std::totally_ordered Key, typename Value>
bool algs4::RedBlackBST<Key, Value>::isBalanced(const Node *h, int black) const {
    if (!h) return black == 0;
    if (!isRed(h)) --black;
    return isBalanced(h->left.get(), black) && isBalanced(h->right.get(), black);
}

template<std::totally_ordered Key, typename Value>
bool algs4::RedBlackBST<Key, Value>::isBalanced() const {
    int black = 0; // number of black links on path from root to min
    for (const Node *x = this->root.get(); x; x = x->left.get())
        if (!isRed(x))
            ++black;
    return isBalanced(this->root.get(), black);
}

template<std::totally_ordered Key, typename Value>
void algs4::RedBlackBST<Key, Value>::put(const Key &key, const Value &val) {
    this->root = put(this->root, key, val);
    this->root->color = BLACK;
    assert(is23());
    assert(isBalanced());
}

template<std::totally_ordered Key, typename Value>
void algs4::RedBlackBST<Key, Value>::remove(const Key &key) {
    if (!isRed(this->root->left.get()) && !isRed(this->root->right.get()))
        this->root->color = RED;
    this->root = remove(this->root, key);
    if (!this->isEmpty()) this->root->color = BLACK;
    assert(is23());
    assert(isBalanced());
}

template<std::totally_ordered Key, typename Value>
void algs4::RedBlackBST<Key, Value>::removeMin() {
    if (!isRed(this->root->left.get()) && !isRed(this->root->right.get()))
        this->root->color = RED;
    this->root = removeMin(this->root);
    if (!this->isEmpty()) this->root->color = BLACK;
    assert(is23());
    assert(isBalanced());
}

template<std::totally_ordered Key, typename Value>
void algs4::RedBlackBST<Key, Value>::removeMax() {
    if (!isRed(this->root->left.get()) && !isRed(this->root->right.get()))
        this->root->color = RED;
    this->root = removeMax(this->root);
    if (!this->isEmpty()) this->root->color = BLACK;
    assert(is23());
    assert(isBalanced());
}


#endif //ALGS4_REDBLACKBST_HPP
