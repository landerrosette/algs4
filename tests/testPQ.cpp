#include "testPQ.h"
#include <iostream>

void testPQ(MaxPQ<std::string> &&pq, std::istream &&data) {
    std::string word;
    while (data >> word) {
        if (word != "-") pq.insert(word);
        else if (!pq.isEmpty()) std::cout << *pq.delMax() << " ";
    }
    std::cout << "(" << pq.size() << " left on pq)" << "\n";
}
