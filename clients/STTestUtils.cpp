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

#include <algorithm>
#include <istream>
#include <iterator>
#include <ostream>
#include <random>
#include <utility>

void STTestUtils::init(algs4::ST<std::string, int> &st, std::istream &is, std::ostream &os) {
    std::string word;
    for (int i = 0; is >> word; ++i)
        st.put(std::move(word), i);
    os << "size = " << st.size() << std::endl;
}

// Print keys using keys().
void STTestUtils::listAll(const algs4::ST<std::string, int> &st, std::ostream &os) {
    for (const auto &s: st.keys()) {
        const int *val = st.get(s);
        os << s << " " << (val ? *val : INVALID_VALUE) << std::endl;
    }
}

// Remove some randomly selected keys.
void STTestUtils::removeSome(algs4::ST<std::string, int> &st, std::ostream &os) {
    auto N = st.size();
    auto keys = st.keys();
    std::vector keysVec(std::make_move_iterator(keys.begin()), std::make_move_iterator(keys.end()));
    std::ranges::shuffle(keysVec, std::default_random_engine(std::random_device()()));
    for (int i = 0; i < N / 2; ++i)
        st.remove(keysVec[i]);
    os << "After removing " << N / 2 << " randomly selected keys, size = " << st.size() << std::endl;
    os << "--------------------------------" << std::endl;
    listAll(st, os);
}

// Remove all the remaining keys.
void STTestUtils::removeAll(algs4::ST<std::string, int> &st, std::ostream &os) {
    for (const auto &s: st.keys())
        st.remove(s);
    os << "After removing the remaining keys, size = " << st.size() << std::endl;
    os << "--------------------------------" << std::endl;
    listAll(st, os);
}

void STTestUtils::testKeys(const algs4::ST<std::string, int> &st, std::ostream &os) {
    os << "Testing keys()" << std::endl;
    os << "--------------------------------" << std::endl;
    listAll(st, os);
}
