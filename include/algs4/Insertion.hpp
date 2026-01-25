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

#ifndef ALGS4_INSERTION_HPP
#define ALGS4_INSERTION_HPP

#include <cassert>
#include <concepts>
#include <vector>

#include "SortUtils.hpp"

namespace algs4 {
namespace Insertion {
    template <typename T>
        requires std::totally_ordered<T> && std::swappable<T>
    constexpr void sort(std::vector<T>& a) {
        using namespace SortUtils::detail;
        auto N = std::ssize(a);
        for (decltype(N) i = 1; i < N; ++i)
            // Insert a[i] among a[i-1], a[i-2], a[i-3]...
            for (auto j = i; j > 0 && less(a[j], a[j - 1]); --j) exch(a, j, j - 1);
        assert(SortUtils::isSorted(a));
    }
}  // namespace Insertion
}  // namespace algs4

#endif  // ALGS4_INSERTION_HPP
