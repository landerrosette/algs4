/*
 * Copyright (C) 2025-2026  landerrosette <57791410+landerrosette@users.noreply.github.com>
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

#ifndef ALGS4_BSTBASE_HPP
#define ALGS4_BSTBASE_HPP

#include <cassert>
#include <cstddef>
#include <memory>
#include <utility>

#include "OrderedST.hpp"
#include "Queue.hpp"

namespace algs4 {
namespace detail {
    template <std::copyable Key, std::movable Value, typename Derived>
        requires std::totally_ordered<Key>
    struct BSTNodeBase {
        Key key;
        Value val;
        std::unique_ptr<Derived> left, right;
        std::ptrdiff_t N;  // number of nodes in subtree rooted here

        BSTNodeBase(Key key, Value val, std::ptrdiff_t N) : key(std::move(key)), val(std::move(val)), N(N) {}
    };

    template <std::copyable Key, std::movable Value, typename Node>
        requires std::totally_ordered<Key>
    class BSTBase : public OrderedST<Key, Value> {
    protected:
        std::unique_ptr<Node> root_;

        constexpr BSTBase() = default;

        const Value* get(const Node* x, const Key& key) const {
            if (!x) return nullptr;
            if (key < x->key)
                return get(x->left.get(), key);
            else if (key > x->key)
                return get(x->right.get(), key);
            else
                return &x->val;
        }

        std::ptrdiff_t size(const Node* x) const {
            if (!x) return 0;
            return x->N;
        }

        const Node* min(const Node* x) const {
            if (!x->left) return x;
            return min(x->left.get());
        }

        const Node* max(const Node* x) const {
            if (!x->right) return x;
            return max(x->right.get());
        }

        const Node* floor(const Node* x, const Key& key) const {
            if (!x) return nullptr;
            if (key == x->key) return x;
            if (key < x->key) return floor(x->left.get(), key);
            if (const Node* t = floor(x->right.get(), key))
                return t;
            else
                return x;
        }

        const Node* ceiling(const Node* x, const Key& key) const {
            if (!x) return nullptr;
            if (key == x->key) return x;
            if (key > x->key) return ceiling(x->right.get(), key);
            if (const Node* t = ceiling(x->left.get(), key))
                return t;
            else
                return x;
        }

        std::ptrdiff_t rank(const Node* x, const Key& key) const {
            if (!x) return 0;
            if (key < x->key)
                return rank(x->left.get(), key);
            else if (key > x->key)
                return 1 /* root */ + size(x->left.get()) /* left subtree */ + rank(x->right.get(), key);
            else
                return size(x->left.get());
        }

        const Node* select(const Node* x, std::ptrdiff_t k) const {
            if (!x) return nullptr;
            if (auto t = size(x->left.get()); t > k)
                return select(x->left.get(), k);
            else if (t < k)
                return select(x->right.get(), k - t - 1);
            else
                return x;
        }

        void keys(const Node* x, Queue<Key>& queue, const Key& lo, const Key& hi) const {
            if (!x) return;
            if (lo < x->key) keys(x->left.get(), queue, lo, hi);
            if (lo <= x->key && hi >= x->key) queue.enqueue(x->key);
            if (hi > x->key) keys(x->right.get(), queue, lo, hi);
        }

    public:
        using OrderedST<Key, Value>::get;
        const Value* get(const Key& key) const override { return get(root_.get(), key); }
        std::ptrdiff_t size() const override { return size(root_.get()); }

        const Key* min() const override {
            if (this->isEmpty()) return nullptr;
            return &min(root_.get())->key;
        }

        const Key* max() const override {
            if (this->isEmpty()) return nullptr;
            return &max(root_.get())->key;
        }

        const Key* floor(const Key& key) const override {
            if (this->isEmpty()) return nullptr;
            const Node* x = floor(root_.get(), key);
            if (!x) return nullptr;
            return &x->key;
        }

        const Key* ceiling(const Key& key) const override {
            if (this->isEmpty()) return nullptr;
            const Node* x = ceiling(root_.get(), key);
            if (!x) return nullptr;
            return &x->key;
        }

        std::ptrdiff_t rank(const Key& key) const override { return rank(root_.get(), key); }

        const Key* select(std::ptrdiff_t k) const override {
            assert(k >= 0 && k < size());
            return &select(root_.get(), k)->key;
        }

        using OrderedST<Key, Value>::keys;
        Queue<Key> keys(const Key& lo, const Key& hi) const override {
            Queue<Key> queue;
            keys(root_.get(), queue, lo, hi);
            return queue;
        }
    };
}  // namespace detail
}  // namespace algs4

#endif  // ALGS4_BSTBASE_HPP
