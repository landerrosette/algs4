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

#ifndef ALGS4_QUICK_HPP
#define ALGS4_QUICK_HPP

#include <algorithm>
#include <concepts>
#include <cstddef>
#include <random>
#include <vector>

#include "SortUtils.hpp"

namespace algs4 {
    namespace Quick {
        namespace internal {
            template<std::totally_ordered T>
            constexpr std::ptrdiff_t partition(std::vector<T> &a, std::ptrdiff_t lo, std::ptrdiff_t hi);

            template<std::totally_ordered T>
            constexpr void sort(std::vector<T> &a, std::ptrdiff_t lo, std::ptrdiff_t hi);
        }

        template<std::totally_ordered T>
        void sort(std::vector<T> &a);
    }
}

template<std::totally_ordered T>
constexpr std::ptrdiff_t algs4::Quick::internal::partition(std::vector<T> &a, std::ptrdiff_t lo, std::ptrdiff_t hi) {
    using namespace SortUtils::internal;
    auto i = lo, j = hi + 1;
    T v = a[lo];
    // Scan right, scan left, check for scan complete, and exchange.
    while (true) {
        while (less(a[++i], v)) if (i == hi) break;
        while (less(v, a[--j])) if (j == lo) break;
        if (i >= j) break;
        exch(a, i, j);
    }
    exch(a, lo, j); // Put v = a[j] into position
    return j;       // with a[lo..j-1] <= a[j] <= a[j+1..hi].
}

template<std::totally_ordered T>
constexpr void algs4::Quick::internal::sort(std::vector<T> &a, std::ptrdiff_t lo, std::ptrdiff_t hi) {
    if (hi <= lo) return;
    auto j = partition(a, lo, hi);
    sort(a, lo, j - 1);
    sort(a, j + 1, hi);
}

template<std::totally_ordered T>
void algs4::Quick::sort(std::vector<T> &a) {
    std::ranges::shuffle(a, std::default_random_engine(std::random_device()()));
    internal::sort(a, 0, std::ssize(a) - 1);
}

#endif // ALGS4_QUICK_HPP
