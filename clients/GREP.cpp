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
 * % more tinyL.txt
 * AC
 * AD
 * AAA
 * ABD
 * ADD
 * BCD
 * ABCCBD
 * BABAAA
 * BABBAAA
 *
 * % ./GREP "(A*B|AC)D" < tinyL.txt
 * ABD
 * ABCCBD
 ******************************************************************************/

#include <iostream>
#include <string>
#include <utility>

#include "algs4/NFA.hpp"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Not enough arguments" << std::endl;
        return 1;
    }
    std::string regexp = "(.*" + std::string(argv[1]) + ".*)";
    algs4::NFA nfa(std::move(regexp));
    for (std::string txt; std::getline(std::cin, txt);)
        if (nfa.recognizes(txt))
            std::cout << txt << std::endl;
    return 0;
}
