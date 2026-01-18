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

#ifndef ALGS4_STTESTUTILS_HPP
#define ALGS4_STTESTUTILS_HPP

#include <iosfwd>
#include <string>

#include "algs4/ST.hpp"

namespace STTestUtils {
    constexpr char INVALID_KEY[] = "-";
    constexpr int INVALID_VALUE = -1;

    void init(algs4::ST<std::string, int> &st, std::istream &is, std::ostream &os);
    void listAll(const algs4::ST<std::string, int> &st, std::ostream &os);
    void removeSome(algs4::ST<std::string, int> &st, std::ostream &os);
    void removeAll(algs4::ST<std::string, int> &st, std::ostream &os);
    void testKeys(const algs4::ST<std::string, int> &st, std::ostream &os);
}

#endif // ALGS4_STTESTUTILS_HPP
