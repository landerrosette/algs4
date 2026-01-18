/*
 * Copyright (C) 2024-2026 landerrosette
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
 * % ./MaxPQ < tinyPQ.txt
 * Q X P (6 left on pq)
 ******************************************************************************/

#include "algs4/MaxPQ.hpp"

#include <iostream>
#include <string>
#include <utility>

int main(int argc, char *argv[]) {
    algs4::MaxPQ<std::string> pq;
    for (std::string item; std::cin >> item;) {
        if (item != "-")
            pq.insert(std::move(item));
        else if (!pq.isEmpty())
            std::cout << pq.delMax() << " ";
    }
    std::cout << "(" << pq.size() << " left on pq)" << std::endl;
    return 0;
}
