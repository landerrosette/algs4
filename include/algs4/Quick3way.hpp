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

#ifndef ALGS4_QUICK3WAY_HPP
#define ALGS4_QUICK3WAY_HPP

#include <algorithm>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <random>
#include <vector>

#include "SortUtils.hpp"

namespace algs4 {
namespace Quick3way {
    namespace detail {
        template <typename T>
            requires std::totally_ordered<T> && std::swappable<T>
        constexpr void sort(std::vector<T>& a, std::ptrdiff_t lo, std::ptrdiff_t hi) {
            using namespace SortUtils::detail;
            if (hi <= lo) return;
            auto lt = lo, i = lo + 1, gt = hi;
            T v = a[lo];
            while (i <= gt) {
                if (a[i] < v)
                    exch(a, lt++, i++);
                else if (a[i] > v)
                    exch(a, i, gt--);
                else
                    ++i;
            }  // Now a[lo..lt-1] < v = a[lt..gt] < a[gt+1..hi].
            sort(a, lo, lt - 1);
            sort(a, gt + 1, hi);
        }
    }  // namespace detail

    template <typename T>
        requires std::totally_ordered<T> && std::swappable<T>
    void sort(std::vector<T>& a) {
        std::ranges::shuffle(a, std::default_random_engine(std::random_device()()));
        detail::sort(a, 0, std::ssize(a) - 1);
        assert(SortUtils::isSorted(a));
    }
}  // namespace Quick3way
}  // namespace algs4

#endif  // ALGS4_QUICK3WAY_HPP
