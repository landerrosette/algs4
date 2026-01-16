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

#include "STTestUtils.hpp"

#include <istream>
#include <ostream>
#include <random>
#include <utility>

namespace STTestUtils {
    void init(algs4::ST<std::string, int> &st, std::istream &is, std::ostream &os) {
        std::string word;
        for (int i = 0; is >> word; ++i)
            st.put(std::move(word), i);
        os << "size = " << st.size() << std::endl;
    }

    // Print keys using keys().
    void listAll(const algs4::ST<std::string, int> &st, std::ostream &os) {
        for (const auto &s: st.keys()) {
            const int *val = st.get(s);
            os << s << " " << (val ? *val : INVALID_VALUE) << std::endl;
        }
    }

    // Remove some randomly selected keys.
    void removeSome(algs4::ST<std::string, int> &st, std::ostream &os) {
        std::default_random_engine e(std::random_device{}());
        std::bernoulli_distribution b;
        int i = 0;
        for (const auto &s: st.keys()) {
            if (b(e)) {
                st.remove(s);
                ++i;
            }
        }
        os << "After removing " << i << " randomly selected keys, size = " << st.size() << std::endl;
        os << "--------------------------------" << std::endl;
        listAll(st, os);
    }

    // Remove all the remaining keys.
    void removeAll(algs4::ST<std::string, int> &st, std::ostream &os) {
        for (const auto &s: st.keys())
            st.remove(s);
        os << "After removing the remaining keys, size = " << st.size() << std::endl;
    }

    void testKeys(const algs4::ST<std::string, int> &st, std::ostream &os) {
        os << "Testing keys()" << std::endl;
        os << "--------------------------------" << std::endl;
        listAll(st, os);
    }
}
