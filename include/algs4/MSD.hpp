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
    namespace detail {
        constexpr int R = 256;  // radix
        constexpr int M = 15;   // cutoff for small subarrays

        namespace Insertion {
            namespace detail {
                constexpr bool less(std::string_view v, std::string_view w, std::ptrdiff_t d) {
                    return SortUtils::detail::less(v.substr(d), w.substr(d));
                }
            }  // namespace detail

            constexpr void sort(std::vector<std::string>& a, std::ptrdiff_t lo, std::ptrdiff_t hi, std::ptrdiff_t d) {
                using namespace detail;
                using namespace SortUtils::detail;
                for (auto i = lo; i <= hi; ++i)
                    for (auto j = i; j > lo && less(a[j], a[j - 1], d); --j) exch(a, j, j - 1);
            }
        }  // namespace Insertion

        constexpr void sort(std::vector<std::string>& a, std::vector<std::string>& aux, std::ptrdiff_t lo,
                            std::ptrdiff_t hi, std::ptrdiff_t d) {
            using namespace detail;
            using namespace StringSortUtils::detail;
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
    }  // namespace detail

    constexpr void sort(std::vector<std::string>& a) {
        auto N = std::ssize(a);
        std::vector<std::string> aux(N);
        detail::sort(a, aux, 0, N - 1, 0);
        assert(SortUtils::isSorted(a));
    }
}  // namespace MSD
}  // namespace algs4

#endif  // ALGS4_MSD_HPP
