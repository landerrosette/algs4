#ifndef ALGS4_TESTSORT_H
#define ALGS4_TESTSORT_H


#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <fstream>
#include <filesystem>

template<class Sorter>
void testSort(const std::filesystem::path &dataFilePath) {
    std::ifstream dataFile(dataFilePath);
    std::vector<std::string> a;
    std::string word;
    while (dataFile >> word) a.push_back(word);
    std::cout << "Before: ";
    Sorter::show(a);
    Sorter::sort(a);
    assert(Sorter::isSorted(a));
    std::cout << "After:  ";
    Sorter::show(a);
}

#endif //ALGS4_TESTSORT_H
