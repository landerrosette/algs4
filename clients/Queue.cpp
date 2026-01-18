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
 * % ./Queue < tobe.txt
 * to be or not to be (2 left on queue)
 ******************************************************************************/

#include "algs4/Queue.hpp"

#include <iostream>
#include <string>
#include <utility>

int main(int argc, char *argv[]) {
    algs4::Queue<std::string> q;
    for (std::string item; std::cin >> item;) {
        if (item != "-")
            q.enqueue(std::move(item));
        else if (!q.isEmpty())
            std::cout << q.dequeue() << " ";
    }
    std::cout << "(" << q.size() << " left on queue)" << std::endl;
    return 0;
}
