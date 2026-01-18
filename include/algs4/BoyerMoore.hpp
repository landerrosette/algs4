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

#ifndef ALGS4_BOYERMOORE_HPP
#define ALGS4_BOYERMOORE_HPP

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

#include "SubstrSearcher.hpp"

namespace algs4 {
    class BoyerMoore : public SubstrSearcher {
    private:
        std::vector<std::ptrdiff_t> right_;
        std::string pat_;

    public:
        constexpr explicit BoyerMoore(std::string pat);

        constexpr std::ptrdiff_t search(std::string_view txt) const override;
    };
}

// Compute skip table.
constexpr algs4::BoyerMoore::BoyerMoore(std::string pat) : pat_(std::move(pat)) {
    auto M = std::ssize(pat_);
    int R = 256;
    right_.assign(R, -1); // -1 for chars not in pattern
    for (decltype(M) j = 0; j < M; ++j)
        right_[static_cast<unsigned char>(pat_[j])] = j; // rightmost position for chars in pattern
}

constexpr std::ptrdiff_t algs4::BoyerMoore::search(std::string_view txt) const {
    auto N = std::ssize(txt), M = std::ssize(pat_);
    for (decltype(N) skip, i = 0; i <= N - M; i += skip) {
        // Does the pattern match the text at position i?
        skip = 0;
        for (auto j = M - 1; j >= 0; --j) {
            if (pat_[j] != txt[i + j]) {
                skip = j - right_[static_cast<unsigned char>(txt[i + j])];
                if (skip < 1) skip = 1;
                break;
            }
        }
        if (skip == 0) return i; // found
    }
    return N; // not found
}

#endif // ALGS4_BOYERMOORE_HPP
