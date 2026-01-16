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

#ifndef ALGS4_STRINGST_HPP
#define ALGS4_STRINGST_HPP

#include <string>
#include <string_view>
#include <vector>

#include "ST.hpp"

namespace algs4 {
    template<typename Value>
    class StringST : public ST<std::string, Value> {
    public:
        virtual constexpr std::string longestPrefixOf(std::string_view s) const = 0;
        virtual constexpr std::vector<std::string> keysWithPrefix(const std::string &pre) const = 0;
        virtual constexpr std::vector<std::string> keysThatMatch(std::string_view pat) const = 0;
    };
}

#endif // ALGS4_STRINGST_HPP
