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

#include "StringSTTestUtils.hpp"

#include <ostream>

namespace STTestUtils {
    void testStringST(const algs4::StringST<int> &st, std::ostream &os) {
        os << "longestPrefixOf(\"shellsort\"):" << std::endl;
        os << "--------------------------------" << std::endl;
        os << st.longestPrefixOf("shellsort") << std::endl;
        os << std::endl;

        os << "longestPrefixOf(\"shell\"):" << std::endl;
        os << "--------------------------------" << std::endl;
        os << st.longestPrefixOf("shell") << std::endl;
        os << std::endl;

        os << "keysWithPrefix(\"shor\"):" << std::endl;
        os << "--------------------------------" << std::endl;
        for (const auto &s: st.keysWithPrefix("shor"))
            os << s << std::endl;
        os << std::endl;

        os << "keysThatMatch(\".he.l.\"):" << std::endl;
        os << "--------------------------------" << std::endl;
        for (const auto &s: st.keysThatMatch(".he.l."))
            os << s << std::endl;
    }
}
