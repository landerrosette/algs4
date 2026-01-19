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

#include <iostream>
#include <string>

#include "algs4/BinaryStdIO.hpp"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Not enough arguments" << std::endl;
        return 1;
    }
    int width = std::stoi(argv[1]);
    if (width < 0) {
        std::cerr << "Width must be nonnegative" << std::endl;
        return 1;
    }
    int cnt;
    for (cnt = 0; !algs4::BinaryStdIO::isEmpty(); ++cnt) {
        if (width == 0) {
            algs4::BinaryStdIO::read<bool>();
            continue;
        }
        if (cnt != 0 && cnt % width == 0) std::cout << std::endl;
        if (algs4::BinaryStdIO::read<bool>()) std::cout << "1";
        else std::cout << "0";
    }
    if (width != 0) std::cout << std::endl;
    std::cout << cnt << " bits" << std::endl;
    return 0;
}
