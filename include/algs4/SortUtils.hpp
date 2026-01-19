/*
 * Copyright (C) 2025-2026 landerrosette <57791410+landerrosette@users.noreply.github.com>
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

#ifndef ALGS4_SORTUTILS_HPP
#define ALGS4_SORTUTILS_HPP

#include <concepts>
#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

namespace algs4 {
    namespace SortUtils {
        namespace internal {
            template<std::totally_ordered T>
            constexpr bool less(const T &v, const T &w) { return v < w; }

            template<std::totally_ordered T>
            constexpr void exch(std::vector<T> &a, std::integral auto i, std::integral auto j);
        }

        template<std::totally_ordered T>
        void show(const std::vector<T> &a);

        template<std::totally_ordered T>
        constexpr bool isSorted(const std::vector<T> &a);
    }
}

template<std::totally_ordered T>
constexpr void algs4::SortUtils::internal::exch(std::vector<T> &a, std::integral auto i, std::integral auto j) {
    using std::swap;
    swap(a[i], a[j]);
}

template<std::totally_ordered T>
void algs4::SortUtils::show(const std::vector<T> &a) {
    for (const auto &item: a)
        std::cout << item << " ";
    std::cout << std::endl;
}

template<std::totally_ordered T>
constexpr bool algs4::SortUtils::isSorted(const std::vector<T> &a) {
    using namespace internal;
    for (std::ptrdiff_t i = 1; i < std::ssize(a); ++i)
        if (less(a[i], a[i - 1])) return false;
    return true;
}

#endif // ALGS4_SORTUTILS_HPP
