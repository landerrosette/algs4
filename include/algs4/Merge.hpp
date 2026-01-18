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

#ifndef ALGS4_MERGE_HPP
#define ALGS4_MERGE_HPP

#include <cassert>
#include <concepts>
#include <cstddef>
#include <utility>
#include <vector>

#include "SortUtils.hpp"

namespace algs4 {
    namespace Merge {
        namespace internal {
            template<std::totally_ordered T>
            constexpr void merge(std::vector<T> &a, std::vector<T> &aux, std::ptrdiff_t lo, std::ptrdiff_t mid,
                                 std::ptrdiff_t hi);

            template<std::totally_ordered T>
            constexpr void sort(std::vector<T> &a, std::vector<T> &aux, std::ptrdiff_t lo, std::ptrdiff_t hi);
        }

        template<std::totally_ordered T>
        constexpr void sort(std::vector<T> &a);
    }
}

template<std::totally_ordered T>
constexpr void algs4::Merge::internal::merge(std::vector<T> &a, std::vector<T> &aux, std::ptrdiff_t lo,
                                             std::ptrdiff_t mid, std::ptrdiff_t hi) {
    using namespace internal;
    using namespace SortUtils::internal;
    auto i = lo, j = mid + 1;
    for (auto k = lo; k <= hi; ++k) aux[k] = std::move(a[k]);
    for (auto k = lo; k <= hi; ++k) {
        if (i > mid) a[k] = std::move(aux[j++]);
        else if (j > hi) a[k] = std::move(aux[i++]);
        else if (less(aux[j], aux[i])) a[k] = std::move(aux[j++]);
        else a[k] = std::move(aux[i++]);
    }
}

template<std::totally_ordered T>
constexpr void algs4::Merge::internal::sort(std::vector<T> &a, std::vector<T> &aux, std::ptrdiff_t lo,
                                            std::ptrdiff_t hi) {
    if (hi <= lo) return;
    auto mid = lo + (hi - lo) / 2;
    sort(a, aux, lo, mid);
    sort(a, aux, mid + 1, hi);
    merge(a, aux, lo, mid, hi);
}

template<std::totally_ordered T>
constexpr void algs4::Merge::sort(std::vector<T> &a) {
    std::vector<T> aux(std::ssize(a));
    internal::sort(a, aux, 0, std::ssize(a) - 1);
    assert(SortUtils::isSorted(a));
}

#endif // ALGS4_MERGE_HPP
