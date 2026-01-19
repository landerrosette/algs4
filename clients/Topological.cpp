/*
 * Copyright (C) 2024-2026 landerrosette <57791410+landerrosette@users.noreply.github.com>
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
 * % ./Topological jobs.txt "/"
 * Calculus
 * Linear Algebra
 * Introduction to CS
 * Advanced Programming
 * Algorithms
 * Theoretical CS
 * Artificial Intelligence
 * Robotics
 * Machine Learning
 * Neural Networks
 * Databases
 * Scientific Computing
 * Computational Biology
 *
 ******************************************************************************/

#include "algs4/Topological.hpp"

#include <iostream>

#include "algs4/SymbolDigraph.hpp"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Not enough arguments" << std::endl;
        return 1;
    }
    try {
        algs4::SymbolDigraph sg(argv[1], *argv[2]);
        algs4::Topological top(sg.G());
        for (int v: top.order())
            std::cout << sg.name(v) << std::endl;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
