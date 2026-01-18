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

#ifndef ALGS4_MSD_HPP
#define ALGS4_MSD_HPP

#include <cassert>
#include <cstddef>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "SortUtils.hpp"
#include "StringSortUtils.h"

namespace algs4 {
    namespace MSD {
        namespace internal {
            constexpr int R = 256; // radix
            constexpr int M = 15;  // cutoff for small subarrays

            constexpr void sort(std::vector<std::string> &a, std::vector<std::string> &aux, std::ptrdiff_t lo,
                                std::ptrdiff_t hi, std::ptrdiff_t d);

            namespace Insertion {
                namespace internal {
                    constexpr bool less(std::string_view v, std::string_view w, std::ptrdiff_t d);
                }

                constexpr void sort(std::vector<std::string> &a, std::ptrdiff_t lo, std::ptrdiff_t hi,
                                    std::ptrdiff_t d);
            }
        }

        constexpr void sort(std::vector<std::string> &a);
    }
}

constexpr void algs4::MSD::internal::sort(std::vector<std::string> &a, std::vector<std::string> &aux, std::ptrdiff_t lo,
                                          std::ptrdiff_t hi, std::ptrdiff_t d) {
    using namespace internal;
    using namespace StringSortUtils::internal;
    if (hi <= lo + M) {
        Insertion::sort(a, lo, hi, d);
        return;
    }
    std::vector<std::ptrdiff_t> count(R + 2);
    // Compute frequency counts.
    for (auto i = lo; i <= hi; ++i) ++count[charAt(a[i], d) + 2];
    // Transform counts to indices.
    for (int r = 0; r < R + 1; ++r) count[r + 1] += count[r];
    // Distribute.
    for (auto i = lo; i <= hi; ++i) aux[count[charAt(a[i], d) + 1]++] = std::move(a[i]);
    // Copy back.
    for (auto i = lo; i <= hi; ++i) a[i] = std::move(aux[i - lo]);
    // Recursively sort for each character value.
    for (int r = 0; r < R; ++r) sort(a, aux, lo + count[r], lo + count[r + 1] - 1, d + 1);
}

constexpr bool algs4::MSD::internal::Insertion::internal::less(std::string_view v, std::string_view w,
                                                               std::ptrdiff_t d) {
    return SortUtils::internal::less(v.substr(d), w.substr(d));
}

constexpr void algs4::MSD::internal::Insertion::sort(std::vector<std::string> &a, std::ptrdiff_t lo, std::ptrdiff_t hi,
                                                     std::ptrdiff_t d) {
    using namespace internal;
    using namespace SortUtils::internal;
    for (auto i = lo; i <= hi; ++i)
        for (auto j = i; j > lo && less(a[j], a[j - 1], d); --j)
            exch(a, j, j - 1);
}

constexpr void algs4::MSD::sort(std::vector<std::string> &a) {
    auto N = std::ssize(a);
    std::vector<std::string> aux(N);
    internal::sort(a, aux, 0, N - 1, 0);
    assert(SortUtils::isSorted(a));
}

#endif // ALGS4_MSD_HPP
