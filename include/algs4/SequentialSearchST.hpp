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

#ifndef ALGS4_SEQUENTIALSEARCHST_HPP
#define ALGS4_SEQUENTIALSEARCHST_HPP

#include <concepts>
#include <cstddef>
#include <memory>
#include <utility>

#include "ST.hpp"

namespace algs4 {
template <std::copyable Key, std::movable Value>
    requires std::equality_comparable<Key>
class SequentialSearchST : public ST<Key, Value> {
private:
    struct Node {
        Key key;
        Value val;
        std::unique_ptr<Node> next;

        Node(Key key, Value val, std::unique_ptr<Node> next)
            : key(std::move(key)), val(std::move(val)), next(std::move(next)) {}
    };

    std::unique_ptr<Node> first_;
    std::ptrdiff_t N_ = 0;

    std::unique_ptr<Node> remove(std::unique_ptr<Node> x, const Key& key) {
        if (!x) return nullptr;
        if (key == x->key) {
            --N_;
            return std::move(x->next);
        }
        x->next = remove(std::move(x->next), key);
        return x;
    }

public:
    void put(Key key, Value val) override {
        for (Node* x = first_.get(); x; x = x->next.get())
            if (key == x->key) {
                x->val = std::move(val);
                return;
            }
        first_ = std::make_unique<Node>(std::move(key), std::move(val), std::move(first_));
        ++N_;
    }

    using ST<Key, Value>::get;
    const Value* get(const Key& key) const override {
        for (const Node* x = first_.get(); x; x = x->next.get())
            if (key == x->key) return &x->val;
        return nullptr;
    }

    void remove(const Key& key) override { first_ = remove(std::move(first_), key); }

    std::ptrdiff_t size() const override { return N_; }

    Queue<Key> keys() const override {
        Queue<Key> queue;
        for (const Node* x = first_.get(); x; x = x->next.get()) queue.enqueue(x->key);
        return queue;
    }
};
}  // namespace algs4

#endif  // ALGS4_SEQUENTIALSEARCHST_HPP
