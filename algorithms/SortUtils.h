#ifndef ALGS4_SORTUTILS_H
#define ALGS4_SORTUTILS_H


#include <concepts>
#include <iostream>
#include <utility>
#include <vector>

namespace algs4 {
    namespace SortUtils {
        namespace internal {
            template<std::totally_ordered T>
            bool less(const T &v, const T &w) { return v < w; }

            template<std::totally_ordered T>
            void exch(std::vector<T> &a, int i, int j) { std::swap(a[i], a[j]); }
        }

        template<std::totally_ordered T>
        void show(const std::vector<T> &a);

        template<std::totally_ordered T>
        bool isSorted(const std::vector<T> &a);
    }
}

template<std::totally_ordered T>
void algs4::SortUtils::show(const std::vector<T> &a) {
    for (const auto &item: a)
        std::cout << item << " ";
    std::cout << std::endl;
}

template<std::totally_ordered T>
bool algs4::SortUtils::isSorted(const std::vector<T> &a) {
    using namespace internal;
    for (int i = 1; i < a.size(); ++i)
        if (less(a[i], a[i - 1])) return false;
    return true;
}


#endif //ALGS4_SORTUTILS_H
