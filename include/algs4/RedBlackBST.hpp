/*
 * Copyright (C) 2024-2026  landerrosette <57791410+landerrosette@users.noreply.github.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef ALGS4_REDBLACKBST_HPP
#define ALGS4_REDBLACKBST_HPP

#include <algorithm>
#include <cassert>
#include <utility>

#include "BSTBase.hpp"

namespace algs4 {
namespace detail {
    template <std::copyable Key, std::movable Value>
        requires std::totally_ordered<Key>
    struct RedBlackBSTNode : BSTNodeBase<Key, Value, RedBlackBSTNode<Key, Value>> {
        bool color;

        RedBlackBSTNode(Key key, Value val, std::ptrdiff_t N, bool color)
            : BSTNodeBase<Key, Value, RedBlackBSTNode>(std::move(key), std::move(val), N), color(color) {}
    };
}  // namespace detail

template <std::copyable Key, std::movable Value>
    requires std::totally_ordered<Key>
class RedBlackBST : public detail::BSTBase<Key, Value, detail::RedBlackBSTNode<Key, Value>> {
private:
    using Node = detail::RedBlackBSTNode<Key, Value>;
    static constexpr bool RED = true, BLACK = false;

    bool isRed(const Node* h) const {
        if (!h) return false;
        return h->color == RED;
    }

    // Make a right-leaning link lean to the left.
    std::unique_ptr<Node> rotateLeft(std::unique_ptr<Node> h) {
        auto x = std::move(h->right);
        h->right = std::move(x->left);
        x->color = h->color;
        h->color = RED;
        x->N = h->N;
        h->N = this->size(h->left.get()) + this->size(h->right.get()) + 1;
        x->left = std::move(h);
        return x;
    }

    // Make a left-leaning link lean to the right.
    std::unique_ptr<Node> rotateRight(std::unique_ptr<Node> h) {
        auto x = std::move(h->left);
        h->left = std::move(x->right);
        x->color = h->color;
        h->color = RED;
        x->N = h->N;
        h->N = this->size(h->left.get()) + this->size(h->right.get()) + 1;
        x->right = std::move(h);
        return x;
    }

    // Flip the colors of a node and its two children.
    void flipColors(Node* h) {
        h->color = !h->color;
        h->left->color = !h->left->color;
        h->right->color = !h->right->color;
    }

    // Assuming that h is red and both h->left and h->left->left are black, make h->left or one of its children red.
    std::unique_ptr<Node> moveRedLeft(std::unique_ptr<Node> h) {
        flipColors(h.get());
        if (isRed(h->right->left.get())) {
            h->right = rotateRight(std::move(h->right));
            h = rotateLeft(std::move(h));
            flipColors(h.get());
        }
        return h;
    }

    // Assuming that h is red and both h->right and h->right->left are black, make h->right or one of its children red.
    std::unique_ptr<Node> moveRedRight(std::unique_ptr<Node> h) {
        flipColors(h.get());
        if (isRed(h->left->left.get())) {
            h = rotateRight(std::move(h));
            flipColors(h.get());
        }
        return h;
    }

    // Restore red-black tree invariant.
    std::unique_ptr<Node> balance(std::unique_ptr<Node> h) {
        if (isRed(h->right.get()) && !isRed(h->left.get())) h = rotateLeft(std::move(h));
        if (isRed(h->left.get()) && isRed(h->left->left.get())) h = rotateRight(std::move(h));
        if (isRed(h->left.get()) && isRed(h->right.get())) flipColors(h.get());
        h->N = this->size(h->left.get()) + this->size(h->right.get()) + 1;
        return h;
    }

    std::unique_ptr<Node> put(std::unique_ptr<Node> h, Key key, Value val) {
        if (!h) return std::make_unique<Node>(std::move(key), std::move(val), 1, RED);
        if (key < h->key)
            h->left = put(std::move(h->left), std::move(key), std::move(val));
        else if (key > h->key)
            h->right = put(std::move(h->right), std::move(key), std::move(val));
        else
            h->val = std::move(val);
        return balance(std::move(h));
    }

    std::unique_ptr<Node> remove(std::unique_ptr<Node> h, const Key& key) {
        if (!h) return nullptr;
        if (key < h->key) {
            if (!isRed(h->left.get()) && !isRed(h->left->left.get())) h = moveRedLeft(std::move(h));
            h->left = remove(std::move(h->left), key);
        } else {
            if (isRed(h->left.get())) h = rotateRight(std::move(h));
            if (key == h->key && !h->right) return nullptr;
            if (!isRed(h->right.get()) && !isRed(h->right->left.get())) h = moveRedRight(std::move(h));
            if (key == h->key) {
                const Node* x = this->min(h->right.get());
                h->key = x->key;
                h->val = x->val;
                h->right = removeMin(std::move(h->right));
            } else
                h->right = remove(std::move(h->right), key);
        }
        return balance(std::move(h));
    }

    std::unique_ptr<Node> removeMin(std::unique_ptr<Node> h) {
        if (!h->left) return nullptr;
        if (!isRed(h->left.get()) && !isRed(h->left->left.get())) h = moveRedLeft(std::move(h));
        h->left = removeMin(std::move(h->left));
        return balance(std::move(h));
    }

    std::unique_ptr<Node> removeMax(std::unique_ptr<Node> h) {
        if (isRed(h->left.get())) h = rotateRight(std::move(h));
        if (!h->right) return nullptr;
        if (!isRed(h->right.get()) && !isRed(h->right->left.get())) h = moveRedRight(std::move(h));
        h->right = removeMax(std::move(h->right));
        return balance(std::move(h));
    }

    int height(const Node* h) const {
        if (!h) return -1;
        return 1 + std::max(height(h->left.get()), height(h->right.get()));
    }

    bool is23(const Node* h) const {
        if (!h) return true;
        if (isRed(h->right.get())) return false;
        if (h != this->root_.get() && isRed(h) && isRed(h->left.get())) return false;
        return is23(h->left.get()) && is23(h->right.get());
    }

    // Does the tree have no red right links, and at most one (left) red links in a row on any path?
    bool is23() const { return is23(this->root_.get()); }

    // Does every path from the root to a leaf have the given number of black links?
    bool isBalanced(const Node* h, int black) const {
        if (!h) return black == 0;
        if (!isRed(h)) --black;
        return isBalanced(h->left.get(), black) && isBalanced(h->right.get(), black);
    }

    // Do all paths from root to leaf have same number of black edges?
    bool isBalanced() const {
        int black = 0;  // number of black links on path from root to min
        for (const Node* x = this->root_.get(); x; x = x->left.get())
            if (!isRed(x)) ++black;
        return isBalanced(this->root_.get(), black);
    }

public:
    void put(Key key, Value val) override {
        this->root_ = put(std::move(this->root_), std::move(key), std::move(val));
        this->root_->color = BLACK;
        assert(is23());
        assert(isBalanced());
    }

    void remove(const Key& key) override {
        if (!isRed(this->root_->left.get()) && !isRed(this->root_->right.get())) this->root_->color = RED;
        this->root_ = remove(std::move(this->root_), key);
        if (!this->isEmpty()) this->root_->color = BLACK;
        assert(is23());
        assert(isBalanced());
    }

    void removeMin() override {
        if (this->isEmpty()) return;
        if (!isRed(this->root_->left.get()) && !isRed(this->root_->right.get())) this->root_->color = RED;
        this->root_ = removeMin(std::move(this->root_));
        if (!this->isEmpty()) this->root_->color = BLACK;
        assert(is23());
        assert(isBalanced());
    }

    void removeMax() override {
        if (this->isEmpty()) return;
        if (!isRed(this->root_->left.get()) && !isRed(this->root_->right.get())) this->root_->color = RED;
        this->root_ = removeMax(std::move(this->root_));
        if (!this->isEmpty()) this->root_->color = BLACK;
        assert(is23());
        assert(isBalanced());
    }

    int height() const { return height(this->root_.get()); }
};
}  // namespace algs4

#endif  // ALGS4_REDBLACKBST_HPP
