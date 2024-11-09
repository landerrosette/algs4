/******************************************************************************
 *  % ./MaxPQ < tinyPQ.txt
 *  Q X P (6 left on pq)
 *
 ******************************************************************************/


#include <iostream>
#include <string>
#include "MaxPQ.h"

int main(int argc, char *argv[]) {
    MaxPQ<std::string> pq(10);
    for (std::string item; std::cin >> item;) {
        if (item != "-") pq.insert(item);
        else if (!pq.isEmpty()) std::cout << *pq.delMax() << " ";
    }
    std::cout << "(" << pq.size() << " left on pq)" << std::endl;
    return 0;
}
