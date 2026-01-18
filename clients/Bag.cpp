/*
 * Copyright (C) 2026 landerrosette
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
 * % more tobe.txt
 * to be or not to - be - - that - - - is
 *
 * % ./Bag < tobe.txt
 * size of bag = 14
 * is
 * -
 * -
 * -
 * that
 * -
 * -
 * be
 * -
 * to
 * not
 * or
 * be
 * to
 ******************************************************************************/

#include "algs4/Bag.hpp"

#include <iostream>
#include <string>
#include <utility>

int main(int argc, char *argv[]) {
    algs4::Bag<std::string> b;
    for (std::string item; std::cin >> item;)
        b.add(std::move(item));
    std::cout << "size of bag = " << b.size() << std::endl;
    for (const auto &item: b)
        std::cout << item << std::endl;
    return 0;
}
