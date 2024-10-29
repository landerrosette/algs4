#ifndef ALGS4_TESTSORT_H
#define ALGS4_TESTSORT_H


#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

template<class Sorter>
void testSort(std::istream &&data);

template<class Sorter>
void testSort(std::istream &&data) {
    static_assert(std::is_base_of_v<Sorting, Sorter>);
    std::vector<std::string> a;
    std::string word;
    while (data >> word) a.push_back(word);
    std::cout << "Before: ";
    Sorter::show(a);
    Sorter::sort(a);
    std::cout << "After:  ";
    Sorter::show(a);
    std::cout << "Sorted? " << (Sorter::isSorted(a) ? "\033[32mYes" : "\033[31mNo") << "\033[0m" << std::endl;
}


#endif //ALGS4_TESTSORT_H
