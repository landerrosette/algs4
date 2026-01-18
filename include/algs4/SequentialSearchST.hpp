/*
 * Copyright (C) 2024 landerrosette
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

#ifndef ALGS4_SEQUENTIALSEARCHST_HPP
#define ALGS4_SEQUENTIALSEARCHST_HPP

#include <cstddef>
#include <memory>
#include <utility>

#include "ST.hpp"

namespace algs4 {
    template<typename Key, typename Value>
    class SequentialSearchST : public ST<Key, Value> {
    private:
        struct Node {
            Key key_;
            Value val_;
            std::unique_ptr<Node> next_;

            Node(Key key, Value val, std::unique_ptr<Node> next)
                : key_(std::move(key)), val_(std::move(val)), next_(std::move(next)) {}
        };

        std::unique_ptr<Node> first_;
        std::ptrdiff_t N_ = 0;

        std::unique_ptr<Node> remove(std::unique_ptr<Node> x, const Key &key);

    public:
        void put(Key key, Value val) override;
        using ST<Key, Value>::get;
        const Value *get(const Key &key) const override;
        void remove(const Key &key) override { first_ = remove(std::move(first_), key); }
        std::ptrdiff_t size() const override { return N_; }
        Queue<Key> keys() const override;
    };
}

template<typename Key, typename Value>
auto algs4::SequentialSearchST<Key, Value>::remove(std::unique_ptr<Node> x, const Key &key) -> std::unique_ptr<Node> {
    if (!x) return nullptr;
    if (key == x->key_) {
        --N_;
        return std::move(x->next_);
    }
    x->next_ = remove(std::move(x->next_), key);
    return x;
}

template<typename Key, typename Value>
void algs4::SequentialSearchST<Key, Value>::put(Key key, Value val) {
    for (Node *x = first_.get(); x; x = x->next_.get())
        if (key == x->key_) {
            x->val_ = std::move(val);
            return;
        }
    first_ = std::make_unique<Node>(std::move(key), std::move(val), std::move(first_));
    ++N_;
}

template<typename Key, typename Value>
const Value *algs4::SequentialSearchST<Key, Value>::get(const Key &key) const {
    for (const Node *x = first_.get(); x; x = x->next_.get())
        if (key == x->key_)
            return &x->val_;
    return nullptr;
}

template<typename Key, typename Value>
algs4::Queue<Key> algs4::SequentialSearchST<Key, Value>::keys() const {
    Queue<Key> queue;
    for (const Node *x = first_.get(); x; x = x->next_.get())
        queue.enqueue(x->key_);
    return queue;
}

#endif // ALGS4_SEQUENTIALSEARCHST_HPP
