/*
 * Copyright (C) 2025 landerrosette
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

#ifndef ALGS4_PQBASE_HPP
#define ALGS4_PQBASE_HPP

#include <cassert>
#include <concepts>
#include <cstddef>
#include <utility>
#include <vector>

namespace algs4 {
    template<typename Key, std::strict_weak_order<Key, Key> Compare>
    class PQBase {
    protected:
        std::vector<Key> pq_;
        [[no_unique_address]] Compare comp_;

        constexpr PQBase() = default;
        constexpr explicit PQBase(const Compare &comp) : comp_(comp) {}
        constexpr ~PQBase() = default;
        constexpr PQBase(const PQBase &) = default;
        constexpr PQBase &operator=(const PQBase &) = default;
        constexpr PQBase(PQBase &&) noexcept = default;
        constexpr PQBase &operator=(PQBase &&) noexcept = default;

        constexpr bool less(std::ptrdiff_t i, std::ptrdiff_t j) { return comp_(pq_[i - 1], pq_[j - 1]); }
        constexpr void exch(std::ptrdiff_t i, std::ptrdiff_t j);
        constexpr void swim(std::ptrdiff_t k);
        constexpr void sink(std::ptrdiff_t k);
        constexpr Key delTop();

    public:
        constexpr bool isEmpty() const { return pq_.empty(); }
        constexpr std::ptrdiff_t size() const { return std::ssize(pq_); }

        template<typename K> requires std::constructible_from<Key, K>
        constexpr void insert(K &&v);
    };
}

template<typename Key, std::strict_weak_order<Key, Key> Compare>
constexpr void algs4::PQBase<Key, Compare>::exch(std::ptrdiff_t i, std::ptrdiff_t j) {
    using std::swap;
    swap(pq_[i - 1], pq_[j - 1]);
}

template<typename Key, std::strict_weak_order<Key, Key> Compare>
constexpr void algs4::PQBase<Key, Compare>::swim(std::ptrdiff_t k) {
    while (k > 1 && less(k / 2, k)) {
        exch(k / 2, k);
        k = k / 2;
    }
}

template<typename Key, std::strict_weak_order<Key, Key> Compare>
constexpr void algs4::PQBase<Key, Compare>::sink(std::ptrdiff_t k) {
    while (2 * k <= size()) {
        auto j = 2 * k;
        if (j < size() && less(j, j + 1))
            ++j;
        if (!less(k, j))
            break;
        exch(k, j);
        k = j;
    }
}

template<typename Key, std::strict_weak_order<Key, Key> Compare>
constexpr Key algs4::PQBase<Key, Compare>::delTop() {
    assert(!isEmpty());
    auto top = std::move(pq_[0]);
    exch(1, size());
    pq_.pop_back();
    sink(1);
    return top;
}

template<typename Key, std::strict_weak_order<Key, Key> Compare>
template<typename K> requires std::constructible_from<Key, K>
constexpr void algs4::PQBase<Key, Compare>::insert(K &&v) {
    pq_.emplace_back(std::forward<K>(v));
    swim(size());
}

#endif // ALGS4_PQBASE_HPP
