/*
 * Copyright (C) 2025-2026  landerrosette <57791410+landerrosette@users.noreply.github.com>
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

#ifndef ALGS4_STRINGSTTESTUTILS_HPP
#define ALGS4_STRINGSTTESTUTILS_HPP

#include <iosfwd>

#include "algs4/StringST.hpp"

namespace STTestUtils {
void testStringST(const algs4::StringST<int>& st, std::ostream& os);
}

#endif  // ALGS4_STRINGSTTESTUTILS_HPP
