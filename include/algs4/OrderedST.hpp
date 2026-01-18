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

#ifndef ALGS4_ORDEREDST_HPP
#define ALGS4_ORDEREDST_HPP

#include <concepts>
#include <cstddef>

#include "Queue.hpp"
#include "ST.hpp"

namespace algs4 {
    template<std::totally_ordered Key, typename Value>
    class OrderedST : public ST<Key, Value> {
    protected:
        constexpr OrderedST() = default;

    public:
        virtual constexpr const Key *min() const = 0;
        virtual constexpr const Key *max() const = 0;
        virtual constexpr const Key *floor(const Key &key) const = 0;
        virtual constexpr const Key *ceiling(const Key &key) const = 0;
        virtual constexpr std::ptrdiff_t rank(const Key &key) const = 0;
        virtual constexpr const Key *select(std::ptrdiff_t k) const = 0;
        virtual constexpr void removeMin();
        virtual constexpr void removeMax();
        using ST<Key, Value>::size;
        constexpr std::ptrdiff_t size(const Key &lo, const Key &hi) const;
        Queue<Key> keys() const override;
        virtual Queue<Key> keys(const Key &lo, const Key &hi) const = 0;
    };
}

template<std::totally_ordered Key, typename Value>
constexpr void algs4::OrderedST<Key, Value>::removeMin() {
    if (this->isEmpty()) return;
    this->remove(*min());
}

template<std::totally_ordered Key, typename Value>
constexpr void algs4::OrderedST<Key, Value>::removeMax() {
    if (this->isEmpty()) return;
    this->remove(*max());
}

template<std::totally_ordered Key, typename Value>
constexpr std::ptrdiff_t algs4::OrderedST<Key, Value>::size(const Key &lo, const Key &hi) const {
    if (hi < lo) return 0;
    else if (this->contains(hi)) return rank(hi) - rank(lo) + 1;
    else return rank(hi) - rank(lo);
}

template<std::totally_ordered Key, typename Value>
algs4::Queue<Key> algs4::OrderedST<Key, Value>::keys() const {
    if (this->isEmpty()) return {};
    return keys(*min(), *max());
}

#endif // ALGS4_ORDEREDST_HPP
