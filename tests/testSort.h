#ifndef ALGS4_TESTSORT_H
#define ALGS4_TESTSORT_H


#include <iostream>
#include <string>
#include <vector>
#include <cassert>

template <class Sorter>
void testSort(std::istream&& data);

template <class Sorter>
void testSort(std::istream&& data) {
    std::vector<std::string> a;
    std::string word;
    while (data >> word) a.push_back(word);
    std::cout << "Before: ";
    Sorter::show(a);
    Sorter::sort(a);
    assert(Sorter::isSorted(a));
    std::cout << "After:  ";
    Sorter::show(a);
}


#endif //ALGS4_TESTSORT_H
