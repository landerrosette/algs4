#ifndef ALGS4_TESTSORT_H
#define ALGS4_TESTSORT_H


#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <fstream>
#include <filesystem>

template<class SortAlgorithm>
void testSort(const std::filesystem::path &dataFilePath) {
    std::ifstream dataFile(dataFilePath);
    std::vector<std::string> a;
    std::string word;
    while (dataFile >> word) a.push_back(word);
    std::cout << "Before: ";
    SortAlgorithm::show(a);
    SortAlgorithm::sort(a);
    assert(SortAlgorithm::isSorted(a));
    std::cout << "After:  ";
    SortAlgorithm::show(a);
}

#endif //ALGS4_TESTSORT_H
