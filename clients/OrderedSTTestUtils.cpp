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

#include "OrderedSTTestUtils.hpp"

#include <array>
#include <iomanip>
#include <istream>
#include <ostream>

#include "STTestUtils.hpp"

void STTestUtils::init(algs4::OrderedST<std::string, int>& st, std::istream& is, std::ostream& os) {
    init(static_cast<algs4::ST<std::string, int>&>(st), is, os);
    const auto *min = st.min(), *max = st.max();
    os << "min  = " << (min ? *min : INVALID_KEY) << std::endl;
    os << "max  = " << (max ? *max : INVALID_KEY) << std::endl;
}

// Remove the smallest keys.
void STTestUtils::removeSome(algs4::OrderedST<std::string, int>& st, std::ostream& os) {
    auto N = st.size();
    for (int i = 0; i < N / 2; ++i) st.removeMin();
    os << "After removing the smallest " << N / 2 << " keys, size = " << st.size() << std::endl;
    os << "--------------------------------" << std::endl;
    listAll(st, os);
}

// Remove all the remaining keys.
void STTestUtils::removeAll(algs4::OrderedST<std::string, int>& st, std::ostream& os) {
    while (!st.isEmpty()) st.remove(*st.select(st.size() / 2));
    os << "After removing the remaining keys, size = " << st.size() << std::endl;
    os << "--------------------------------" << std::endl;
    listAll(st, os);
}

void STTestUtils::testOrderedST(const algs4::OrderedST<std::string, int>& st, std::ostream& os) {
    // Print keys in order using select.
    os << "Testing select" << std::endl;
    os << "--------------------------------" << std::endl;
    for (int i = 0; i < st.size(); ++i) os << i << " " << *st.select(i) << std::endl;
    os << std::endl;

    // Test rank, floor, ceiling.
    os << "key rank floor ceil" << std::endl;
    os << "-------------------" << std::endl;
    for (char i = 'A'; i <= 'Z'; ++i) {
        std::string s(1, i);
        const auto *floor = st.floor(s), *ceiling = st.ceiling(s);
        os << std::setw(2) << s << " " << std::setw(4) << st.rank(s) << " " << std::setw(4)
           << (floor ? *floor : INVALID_KEY) << " " << std::setw(4) << (ceiling ? *ceiling : INVALID_KEY) << std::endl;
    }
    os << std::endl;

    // Test range search and range count.
    std::array<std::string, 6> from = {"A", "Z", "X", "0", "B", "C"};
    std::array<std::string, 6> to = {"Z", "A", "X", "Z", "G", "L"};
    os << "range search" << std::endl;
    os << "-------------------" << std::endl;
    for (int i = 0; i < std::ssize(from); ++i) {
        os << from[i] << "-" << to[i] << " (" << std::setw(2) << st.size(from[i], to[i]) << ") : ";
        for (const auto& s : st.keys(from[i], to[i])) os << s << " ";
        os << std::endl;
    }
}
