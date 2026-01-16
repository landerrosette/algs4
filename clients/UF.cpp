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

/******************************************************************************
 * % ./UF < tinyUF.txt
 * 4 3
 * 3 8
 * 6 5
 * 9 4
 * 2 1
 * 5 0
 * 7 2
 * 6 1
 * 2 components
 *
 ******************************************************************************/

#include "algs4/UF.hpp"

#include <iostream>

int main(int argc, char *argv[]) {
    int N;
    std::cin >> N;
    if (N < 0) {
        std::cerr << "Number of sites must be nonnegative" << std::endl;
        return 1;
    }
    algs4::UF uf(N);
    for (int p, q; std::cin >> p >> q;) {
        if (p < 0 || p >= N || q < 0 || q >= N) {
            std::cerr << "Index out of bounds" << std::endl;
            return 1;
        }
        if (uf.connected(p, q)) continue;
        uf.unionize(p, q);
        std::cout << p << " " << q << std::endl;
    }
    std::cout << uf.count() << " components" << std::endl;
    return 0;
}
