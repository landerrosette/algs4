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
 * % ./DirectedDFS tinyDG.txt 1
 * 1
 *
 * % ./DirectedDFS tinyDG.txt 2
 * 0 1 2 3 4 5
 *
 * % ./DirectedDFS tinyDG.txt 1 2 6
 * 0 1 2 3 4 5 6 8 9 10 11 12
 ******************************************************************************/

#include "algs4/DirectedDFS.hpp"

#include <fstream>
#include <iostream>
#include <string>

#include "algs4/Bag.hpp"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Not enough arguments" << std::endl;
        return 1;
    }
    std::ifstream in(argv[1]);
    if (!in.is_open()) {
        std::cerr << "Cannot open file: " << argv[1] << std::endl;
        return 1;
    }
    algs4::Digraph G(in);
    algs4::Bag<int> sources;
    for (int i = 2; i < argc; ++i) {
        int s = std::stoi(argv[i]);
        if (s < 0 || s >= G.V()) {
            std::cerr << "Source vertex out of range" << std::endl;
            return 1;
        }
        sources.add(s);
    }
    algs4::DirectedDFS reachable(G, sources);
    for (int v = 0; v < G.V(); ++v)
        if (reachable.marked(v))
            std::cout << v << " ";
    std::cout << std::endl;
    return 0;
}
