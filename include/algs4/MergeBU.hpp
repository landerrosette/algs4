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

#ifndef ALGS4_MERGEBU_HPP
#define ALGS4_MERGEBU_HPP

#include <algorithm>
#include <cassert>
#include <concepts>
#include <vector>

#include "Merge.hpp"

namespace algs4 {
namespace MergeBU {
    template <typename T>
        requires std::totally_ordered<T> && std::swappable<T>
    constexpr void sort(std::vector<T>& a) {
        using namespace Merge::detail;
        auto N = std::ssize(a);
        std::vector<T> aux(N);
        for (decltype(N) sz = 1; sz < N; sz = sz + sz)            // sz: subarray size
            for (decltype(N) lo = 0; lo < N - sz; lo += sz + sz)  // lo: subarray index
                merge(a, aux, lo, lo + sz - 1, std::min(lo + sz + sz - 1, N - 1));
        assert(SortUtils::isSorted(a));
    }
}  // namespace MergeBU
}  // namespace algs4

#endif  // ALGS4_MERGEBU_HPP
