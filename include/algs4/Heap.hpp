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

#ifndef ALGS4_HEAP_HPP
#define ALGS4_HEAP_HPP

#include <cassert>
#include <concepts>
#include <cstddef>
#include <vector>

#include "SortUtils.hpp"

namespace algs4 {
    namespace Heap {
        namespace internal {
            template<std::totally_ordered T>
            constexpr bool less(const std::vector<T> &a, std::ptrdiff_t i, std::ptrdiff_t j);

            template<std::totally_ordered T>
            constexpr void exch(std::vector<T> &a, std::ptrdiff_t i, std::ptrdiff_t j);

            template<std::totally_ordered T>
            constexpr void sink(std::vector<T> &a, std::ptrdiff_t k, std::ptrdiff_t N);
        }

        template<std::totally_ordered T>
        constexpr void sort(std::vector<T> &a);
    }
}

template<std::totally_ordered T>
constexpr bool algs4::Heap::internal::less(const std::vector<T> &a, std::ptrdiff_t i, std::ptrdiff_t j) {
    return SortUtils::internal::less(a[i - 1], a[j - 1]);
}

template<std::totally_ordered T>
constexpr void algs4::Heap::internal::exch(std::vector<T> &a, std::ptrdiff_t i, std::ptrdiff_t j) {
    SortUtils::internal::exch(a, i - 1, j - 1);
}

template<std::totally_ordered T>
constexpr void algs4::Heap::internal::sink(std::vector<T> &a, std::ptrdiff_t k, std::ptrdiff_t N) {
    while (2 * k <= N) {
        auto j = 2 * k;
        if (j < N && less(a, j, j + 1))
            ++j;
        if (!less(a, k, j))
            break;
        exch(a, k, j);
        k = j;
    }
}

template<std::totally_ordered T>
constexpr void algs4::Heap::sort(std::vector<T> &a) {
    using namespace internal;
    auto N = std::ssize(a);
    for (auto k = N / 2; k >= 1; --k)
        sink(a, k, N);
    while (N > 1) {
        exch(a, 1, N--);
        sink(a, 1, N);
    }
    assert(SortUtils::isSorted(a));
}

#endif // ALGS4_HEAP_HPP
