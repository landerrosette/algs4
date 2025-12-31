/******************************************************************************
 *  % ./MaxPQ < tinyPQ.txt
 *  Q X P (6 left on pq)
 *
 ******************************************************************************/


#include "algs4/MaxPQ.hpp"

#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    algs4::MaxPQ<std::string> pq(10);
    for (std::string item; std::cin >> item;) {
        if (item != "-")
            pq.insert(item);
        else if (!pq.isEmpty())
            std::cout << *pq.delMax() << " ";
    }
    std::cout << "(" << pq.size() << " left on pq)" << std::endl;
    return 0;
}
