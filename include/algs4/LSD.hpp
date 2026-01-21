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

#ifndef ALGS4_LSD_HPP
#define ALGS4_LSD_HPP

#include <cassert>
#include <cstddef>
#include <string>
#include <utility>
#include <vector>

#include "SortUtils.hpp"
#include "StringSortUtils.h"

namespace algs4 {
    namespace LSD {
        constexpr void sort(std::vector<std::string> &a, std::ptrdiff_t W = 3);
    }
}

constexpr void algs4::LSD::sort(std::vector<std::string> &a, std::ptrdiff_t W) {
    using namespace StringSortUtils::detail;
    auto N = std::ssize(a);
    int R = 256;
    std::vector<std::string> aux(N);

    for (auto d = W - 1; d >= 0; --d) {
        std::vector<std::ptrdiff_t> count(R + 1);
        // Compute frequency counts.
        for (decltype(N) i = 0; i < N; ++i) ++count[charAt(a[i], d) + 1];
        // Transform counts to indices.
        for (int r = 0; r < R; ++r) count[r + 1] += count[r];
        // Distribute.
        for (decltype(N) i = 0; i < N; ++i) aux[count[charAt(a[i], d)]++] = std::move(a[i]);
        // Copy back.
        for (decltype(N) i = 0; i < N; ++i) a[i] = std::move(aux[i]);
    }

    assert(SortUtils::isSorted(a));
}

#endif // ALGS4_LSD_HPP
