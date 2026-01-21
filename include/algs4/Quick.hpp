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

#ifndef ALGS4_QUICK_HPP
#define ALGS4_QUICK_HPP

#include <algorithm>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <random>
#include <vector>

#include "SortUtils.hpp"

namespace algs4 {
    namespace Quick {
        namespace detail {
            template<typename T> requires std::totally_ordered<T> && std::swappable<T>
            constexpr std::ptrdiff_t partition(std::vector<T> &a, std::ptrdiff_t lo, std::ptrdiff_t hi);

            template<typename T> requires std::totally_ordered<T> && std::swappable<T>
            constexpr void sort(std::vector<T> &a, std::ptrdiff_t lo, std::ptrdiff_t hi);
        }

        template<typename T> requires std::totally_ordered<T> && std::swappable<T>
        void sort(std::vector<T> &a);
    }
}

template<typename T> requires std::totally_ordered<T> && std::swappable<T>
constexpr std::ptrdiff_t algs4::Quick::detail::partition(std::vector<T> &a, std::ptrdiff_t lo, std::ptrdiff_t hi) {
    using namespace SortUtils::detail;
    auto i = lo, j = hi + 1;
    T v = a[lo];
    while (true) {
        // Scan right, scan left, check for scan complete, and exchange.
        while (less(a[++i], v)) if (i == hi) break;
        while (less(v, a[--j])) if (j == lo) break;
        if (i >= j) break;
        exch(a, i, j);
    }
    exch(a, lo, j); // Put v = a[j] into position
    return j;       // with a[lo..j-1] <= a[j] <= a[j+1..hi].
}

template<typename T> requires std::totally_ordered<T> && std::swappable<T>
constexpr void algs4::Quick::detail::sort(std::vector<T> &a, std::ptrdiff_t lo, std::ptrdiff_t hi) {
    if (hi <= lo) return;
    auto j = partition(a, lo, hi);
    sort(a, lo, j - 1);
    sort(a, j + 1, hi);
}

template<typename T> requires std::totally_ordered<T> && std::swappable<T>
void algs4::Quick::sort(std::vector<T> &a) {
    std::ranges::shuffle(a, std::default_random_engine(std::random_device()()));
    detail::sort(a, 0, std::ssize(a) - 1);
    assert(SortUtils::isSorted(a));
}

#endif // ALGS4_QUICK_HPP
