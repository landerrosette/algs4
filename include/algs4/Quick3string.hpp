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

#ifndef ALGS4_QUICK3STRING_HPP
#define ALGS4_QUICK3STRING_HPP

#include <cstddef>
#include <string>
#include <vector>

#include "SortUtils.hpp"
#include "StringSortUtils.h"

namespace algs4 {
    namespace Quick3string {
        namespace internal {
            constexpr void sort(std::vector<std::string> &a, std::ptrdiff_t lo, std::ptrdiff_t hi, std::ptrdiff_t d);
        }

        constexpr void sort(std::vector<std::string> &a) { internal::sort(a, 0, std::ssize(a) - 1, 0); }
    }
}

constexpr void algs4::Quick3string::internal::sort(std::vector<std::string> &a, std::ptrdiff_t lo, std::ptrdiff_t hi,
                                                   std::ptrdiff_t d) {
    using namespace SortUtils::internal;
    using namespace StringSortUtils::internal;
    if (hi <= lo) return;
    auto lt = lo, i = lo + 1, gt = hi;
    int v = charAt(a[lo], d);
    while (i <= gt) {
        int t = charAt(a[i], d);
        if (t < v) exch(a, lt++, i++);
        else if (t > v) exch(a, i, gt--);
        else ++i;
    } // a[lo..lt-1] < v = a[lt..gt] < a[gt+1..hi]
    sort(a, lo, lt - 1, d);
    if (v >= 0) sort(a, lt, gt, d + 1);
    sort(a, gt + 1, hi, d);
}

#endif // ALGS4_QUICK3STRING_HPP
