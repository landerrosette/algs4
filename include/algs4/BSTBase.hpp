/*
 * Copyright (C) 2025-2026 landerrosette
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
    namespace internal {
        template<std::totally_ordered Key, typename Value, typename Derived>
        struct BSTNodeBase {
            Key key_;
            Value val_;
            std::unique_ptr<Derived> left_, right_;
            std::ptrdiff_t N_; // number of nodes in subtree rooted here

            BSTNodeBase(Key key, Value val, std::ptrdiff_t N) : key_(std::move(key)), val_(std::move(val)), N_(N) {}
        };
    }

    template<std::totally_ordered Key, typename Value, typename Node>
    class BSTBase : public OrderedST<Key, Value> {
    protected:
        std::unique_ptr<Node> root_;

        constexpr BSTBase() = default;

        const Value *get(const Node *x, const Key &key) const;
        std::ptrdiff_t size(const Node *x) const;
        const Node *min(const Node *x) const;
        const Node *max(const Node *x) const;
        const Node *floor(const Node *x, const Key &key) const;
        const Node *ceiling(const Node *x, const Key &key) const;
        std::ptrdiff_t rank(const Node *x, const Key &key) const;
        const Node *select(const Node *x, std::ptrdiff_t k) const;
        void keys(const Node *x, Queue<Key> &queue, const Key &lo, const Key &hi) const;

    public:
        using OrderedST<Key, Value>::get;
        const Value *get(const Key &key) const override { return get(root_.get(), key); }
        std::ptrdiff_t size() const override { return size(root_.get()); }
        const Key *min() const override;
        const Key *max() const override;
        const Key *floor(const Key &key) const override;
        const Key *ceiling(const Key &key) const override;
        std::ptrdiff_t rank(const Key &key) const override { return rank(root_.get(), key); }
        const Key *select(std::ptrdiff_t k) const override;
        using OrderedST<Key, Value>::keys;
        Queue<Key> keys(const Key &lo, const Key &hi) const override;
    };
}

template<std::totally_ordered Key, typename Value, typename Node>
const Value *algs4::BSTBase<Key, Value, Node>::get(const Node *x, const Key &key) const {
    if (!x) return nullptr;
    if (key < x->key_) return get(x->left_.get(), key);
    else if (key > x->key_) return get(x->right_.get(), key);
    else return &x->val_;
}

template<std::totally_ordered Key, typename Value, typename Node>
std::ptrdiff_t algs4::BSTBase<Key, Value, Node>::size(const Node *x) const {
    if (!x) return 0;
    return x->N_;
}

template<std::totally_ordered Key, typename Value, typename Node>
const Node *algs4::BSTBase<Key, Value, Node>::min(const Node *x) const {
    if (!x->left_) return x;
    return min(x->left_.get());
}

template<std::totally_ordered Key, typename Value, typename Node>
const Node *algs4::BSTBase<Key, Value, Node>::max(const Node *x) const {
    if (!x->right_) return x;
    return max(x->right_.get());
}

template<std::totally_ordered Key, typename Value, typename Node>
const Node *algs4::BSTBase<Key, Value, Node>::floor(const Node *x, const Key &key) const {
    if (!x) return nullptr;
    if (key == x->key_) return x;
    if (key < x->key_) return floor(x->left_.get(), key);
    if (const Node *t = floor(x->right_.get(), key)) return t;
    else return x;
}

template<std::totally_ordered Key, typename Value, typename Node>
const Node *algs4::BSTBase<Key, Value, Node>::ceiling(const Node *x, const Key &key) const {
    if (!x) return nullptr;
    if (key == x->key_) return x;
    if (key > x->key_) return ceiling(x->right_.get(), key);
    if (const Node *t = ceiling(x->left_.get(), key)) return t;
    else return x;
}

template<std::totally_ordered Key, typename Value, typename Node>
std::ptrdiff_t algs4::BSTBase<Key, Value, Node>::rank(const Node *x, const Key &key) const {
    if (!x) return 0;
    if (key < x->key_) return rank(x->left_.get(), key);
    else if (key > x->key_) return 1 /* root */ + size(x->left_.get()) /* left subtree */ + rank(x->right_.get(), key);
    else return size(x->left_.get());
}

template<std::totally_ordered Key, typename Value, typename Node>
const Node *algs4::BSTBase<Key, Value, Node>::select(const Node *x, std::ptrdiff_t k) const {
    if (!x) return nullptr;
    if (auto t = size(x->left_.get()); t > k) return select(x->left_.get(), k);
    else if (t < k) return select(x->right_.get(), k - t - 1);
    else return x;
}

template<std::totally_ordered Key, typename Value, typename Node>
void algs4::BSTBase<Key, Value, Node>::keys(const Node *x, Queue<Key> &queue,
                                            const Key &lo, const Key &hi) const {
    if (!x) return;
    if (lo < x->key_) keys(x->left_.get(), queue, lo, hi);
    if (lo <= x->key_ && hi >= x->key_) queue.enqueue(x->key_);
    if (hi > x->key_) keys(x->right_.get(), queue, lo, hi);
}

template<std::totally_ordered Key, typename Value, typename Node>
const Key *algs4::BSTBase<Key, Value, Node>::min() const {
    if (this->isEmpty()) return nullptr;
    return &min(root_.get())->key_;
}

template<std::totally_ordered Key, typename Value, typename Node>
const Key *algs4::BSTBase<Key, Value, Node>::max() const {
    if (this->isEmpty()) return nullptr;
    return &max(root_.get())->key_;
}

template<std::totally_ordered Key, typename Value, typename Node>
const Key *algs4::BSTBase<Key, Value, Node>::floor(const Key &key) const {
    if (this->isEmpty()) return nullptr;
    const Node *x = floor(root_.get(), key);
    if (!x) return nullptr;
    return &x->key_;
}

template<std::totally_ordered Key, typename Value, typename Node>
const Key *algs4::BSTBase<Key, Value, Node>::ceiling(const Key &key) const {
    if (this->isEmpty()) return nullptr;
    const Node *x = ceiling(root_.get(), key);
    if (!x) return nullptr;
    return &x->key_;
}

template<std::totally_ordered Key, typename Value, typename Node>
const Key *algs4::BSTBase<Key, Value, Node>::select(std::ptrdiff_t k) const {
    assert(k >= 0 && k < size());
    return &select(root_.get(), k)->key_;
}

template<std::totally_ordered Key, typename Value, typename Node>
algs4::Queue<Key> algs4::BSTBase<Key, Value, Node>::keys(const Key &lo, const Key &hi) const {
    Queue<Key> queue;
    keys(root_.get(), queue, lo, hi);
    return queue;
}

#endif // ALGS4_BSTBASE_HPP
