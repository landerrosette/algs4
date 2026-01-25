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

#include "BalancedTreeTestUtils.hpp"

#include <ostream>
#include <random>

void STTestUtils::testRedBlackBST(algs4::RedBlackBST<int, int>& st, int n, std::ostream& os) {
    // Insert N elements in order.
    os << "Inserting " << n << " elements in order" << std::endl;
    os << "--------------------------------" << std::endl;
    for (int i = 0; i < n; ++i) {
        st.put(i, i);
        os << "i = " << i << ", height = " << st.height() << ", size = " << st.size() << std::endl;
    }
    os << std::endl;

    // Delete keys in random order.
    os << "Deleting keys in random order" << std::endl;
    os << "--------------------------------" << std::endl;
    std::default_random_engine e(std::random_device{}());
    std::uniform_int_distribution u(0, n - 1);
    while (st.size() > 0) {
        if (int i = u(e); st.contains(i)) {
            st.remove(i);
            os << "i = " << i << ", height = " << st.height() << ", size = " << st.size() << std::endl;
        }
    }
    os << std::endl;

    os << "size = " << st.size() << std::endl;
}
