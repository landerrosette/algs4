#include "testPQ.h"
#include <fstream>
#include <iostream>

void testPQ(MaxPQ<std::string> &&pq, const std::filesystem::path &dataFilePath) {
    std::ifstream dataFile(dataFilePath);
    std::string word;
    while (dataFile >> word) {
        if (word != "-") {
            pq.insert(word);
        } else if (!pq.isEmpty()) {
            std::cout << *pq.delMax() << " ";
        }
    }
    std::cout << "(" << pq.size() << " left on pq)" << "\n";
}
