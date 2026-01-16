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

#ifndef ALGS4_SHELL_HPP
#define ALGS4_SHELL_HPP

#include <concepts>
#include <vector>

#include "SortUtils.hpp"

namespace algs4 {
    namespace Shell {
        template<std::totally_ordered T>
        constexpr void sort(std::vector<T> &a);
    }
}

template<std::totally_ordered T>
constexpr void algs4::Shell::sort(std::vector<T> &a) {
    using namespace SortUtils::internal;
    auto N = std::ssize(a);
    decltype(N) h = 1;
    while (h < N / 3) h = h * 3 + 1;
    while (h >= 1) {
        // Insert a[i] among a[i-h], a[i-2*h], a[i-3*h]...
        for (auto i = h; i < N; ++i)
            for (auto j = i; j >= h && less(a[j], a[j - h]); j -= h)
                exch(a, j, j - h);
        h /= 3;
    }
}

#endif // ALGS4_SHELL_HPP
