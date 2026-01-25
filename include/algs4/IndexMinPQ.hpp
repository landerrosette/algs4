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

#ifndef ALGS4_INDEXMINPQ_HPP
#define ALGS4_INDEXMINPQ_HPP

#include <cassert>
#include <concepts>
#include <cstddef>
#include <optional>
#include <utility>
#include <vector>

namespace algs4 {
template <typename Key>
    requires std::movable<Key> && std::totally_ordered<Key>
class IndexMinPQ {
private:
    std::ptrdiff_t N_ = 0;
    std::vector<std::ptrdiff_t> pq_;        // binary heap using 1-based indexing
    std::vector<std::ptrdiff_t> qp_;        // inverse: qp_[pq_[i]] = pq_[qp_[i]] = i
    std::vector<std::optional<Key>> keys_;  // items with priorities

    constexpr bool greater(std::ptrdiff_t i, std::ptrdiff_t j) const { return keys_[pq_[i]] > keys_[pq_[j]]; }

    constexpr void exch(std::ptrdiff_t i, std::ptrdiff_t j) {
        using std::swap;
        swap(pq_[i], pq_[j]);
        qp_[pq_[i]] = i;
        qp_[pq_[j]] = j;
    }

    constexpr void swim(std::ptrdiff_t k) {
        while (k > 1 && greater(k / 2, k)) {
            exch(k / 2, k);
            k = k / 2;
        }
    }

    constexpr void sink(std::ptrdiff_t k) {
        while (2 * k <= N_) {
            auto j = 2 * k;
            if (j < N_ && greater(j, j + 1)) ++j;
            if (!greater(k, j)) break;
            exch(k, j);
            k = j;
        }
    }

public:
    constexpr explicit IndexMinPQ(std::ptrdiff_t maxN) : pq_(maxN + 1), qp_(maxN + 1, -1), keys_(maxN + 1) {
        assert(maxN >= 0);
    }

    constexpr bool isEmpty() const { return N_ == 0; }

    constexpr bool contains(std::ptrdiff_t k) const {
        assert(k >= 0 && k < std::ssize(qp_) - 1);
        return qp_[k] != -1;
    }

    template <std::convertible_to<Key> K>
    constexpr void insert(std::ptrdiff_t k, K&& key) {
        assert(k >= 0 && k < std::ssize(qp_) - 1);
        assert(!contains(k));
        qp_[k] = ++N_;
        pq_[N_] = k;
        keys_[k].emplace(std::forward<K>(key));
        swim(N_);
    }

    template <std::convertible_to<Key> K>
    constexpr void change(std::ptrdiff_t k, K&& key) {
        assert(k >= 0 && k < std::ssize(qp_) - 1);
        assert(contains(k));
        keys_[k].emplace(std::forward<K>(key));
        swim(qp_[k]);
        sink(qp_[k]);
    }

    constexpr std::ptrdiff_t delMin() {
        assert(!isEmpty());
        auto indexOfMin = pq_[1];
        exch(1, N_--);
        sink(1);
        keys_[pq_[N_ + 1]] = std::nullopt;
        qp_[pq_[N_ + 1]] = -1;
        return indexOfMin;
    }
};
}  // namespace algs4

#endif  // ALGS4_INDEXMINPQ_HPP
