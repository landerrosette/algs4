/*
 * Copyright (C) 2024-2026 landerrosette <57791410+landerrosette@users.noreply.github.com>
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

#ifndef ALGS4_LINEARPROBINGHASHST_HPP
#define ALGS4_LINEARPROBINGHASHST_HPP

#include <cstddef>
#include <functional>
#include <optional>
#include <utility>
#include <vector>

#include "Queue.hpp"
#include "ST.hpp"

namespace algs4 {
    template<typename Key, typename Value>
    class LinearProbingHashST : public ST<Key, Value> {
    private:
        std::ptrdiff_t N_ = 0;  // number of key-value pairs in the table
        std::ptrdiff_t M_ = 16; // size of linear-probing table
        std::vector<std::optional<Key> > keys_;
        std::vector<std::optional<Value> > vals_;

        explicit constexpr LinearProbingHashST(std::ptrdiff_t M) : M_(M), keys_(M), vals_(M) {}

        constexpr auto hash(const Key &key) const { return std::hash<Key>()(key) % M_; }
        constexpr void resize(std::ptrdiff_t cap);

    public:
        constexpr LinearProbingHashST() : keys_(M_), vals_(M_) {}

        constexpr void put(Key key, Value val) override;
        using ST<Key, Value>::get;
        constexpr const Value *get(const Key &key) const override;
        constexpr void remove(const Key &key) override;
        constexpr std::ptrdiff_t size() const override { return N_; }
        Queue<Key> keys() const override;
    };
}

template<typename Key, typename Value>
constexpr void algs4::LinearProbingHashST<Key, Value>::resize(std::ptrdiff_t cap) {
    LinearProbingHashST t(cap);
    for (decltype(M_) i = 0; i < M_; ++i)
        if (keys_[i])
            t.put(std::move(*keys_[i]), std::move(*vals_[i]));
    keys_ = std::move(t.keys_);
    vals_ = std::move(t.vals_);
    M_ = t.M_;
}

template<typename Key, typename Value>
constexpr void algs4::LinearProbingHashST<Key, Value>::put(Key key, Value val) {
    if (N_ >= M_ / 2) resize(2 * M_);

    auto i = hash(key);
    for (; keys_[i]; i = (i + 1) % M_)
        if (keys_[i] == key) {
            vals_[i] = std::move(val);
            return;
        }
    keys_[i] = std::move(key);
    vals_[i] = std::move(val);
    ++N_;
}

template<typename Key, typename Value>
constexpr const Value *algs4::LinearProbingHashST<Key, Value>::get(const Key &key) const {
    for (auto i = hash(key); keys_[i]; i = (i + 1) % M_)
        if (keys_[i] == key)
            return &*vals_[i];
    return nullptr;
}

template<typename Key, typename Value>
constexpr void algs4::LinearProbingHashST<Key, Value>::remove(const Key &key) {
    if (!this->contains(key)) return;
    auto i = hash(key);
    while (keys_[i] != key) i = (i + 1) % M_;
    keys_[i] = std::nullopt;
    vals_[i] = std::nullopt;
    i = (i + 1) % M_;
    while (keys_[i]) {
        Key keyToRedo = std::move(*keys_[i]);
        Value valToRedo = std::move(*vals_[i]);
        keys_[i] = std::nullopt;
        vals_[i] = std::nullopt;
        --N_;
        put(std::move(keyToRedo), std::move(valToRedo));
        i = (i + 1) % M_;
    }
    --N_;
    if (N_ > 0 && N_ == M_ / 8) resize(M_ / 2);
}

template<typename Key, typename Value>
algs4::Queue<Key> algs4::LinearProbingHashST<Key, Value>::keys() const {
    Queue<Key> queue;
    for (decltype(M_) i = 0; i < M_; ++i)
        if (keys_[i]) queue.enqueue(*keys_[i]);
    return queue;
}

#endif // ALGS4_LINEARPROBINGHASHST_HPP
