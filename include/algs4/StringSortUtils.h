/*
 * Copyright (C) 2026  landerrosette <57791410+landerrosette@users.noreply.github.com>
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

#ifndef ALGS4_STRINGSORTUTILS_H
#define ALGS4_STRINGSORTUTILS_H

#include <cassert>
#include <cstddef>
#include <string>

namespace algs4 {
namespace StringSortUtils {
    namespace detail {
        constexpr int charAt(const std::string& s, std::ptrdiff_t d) {
            assert(d >= 0 && d <= std::ssize(s));
            if (d == std::ssize(s)) return -1;
            return static_cast<unsigned char>(s[d]);
        }
    }  // namespace detail
}  // namespace StringSortUtils
}  // namespace algs4

#endif  // ALGS4_STRINGSORTUTILS_H
