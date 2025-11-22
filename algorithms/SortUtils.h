#ifndef ALGS4_SORTUTILS_H
#define ALGS4_SORTUTILS_H


#include <iostream>
#include <utility>
#include <vector>

namespace algs4 {
    namespace SortUtils {
        template<typename T>
        void show(const std::vector<T> &a);

        template<typename T>
        bool isSorted(const std::vector<T> &a);
    }

    namespace SortUtils::internal {
        template<typename T>
        bool less(const T &v, const T &w) { return v < w; }

        template<typename T>
        void exch(std::vector<T> &a, int i, int j) { std::swap(a[i], a[j]); }
    }
}

template<typename T>
void algs4::SortUtils::show(const std::vector<T> &a) {
    for (const auto &item: a)
        std::cout << item << " ";
    std::cout << std::endl;
}

template<typename T>
bool algs4::SortUtils::isSorted(const std::vector<T> &a) {
    using namespace internal;
    for (int i = 1; i < a.size(); ++i) {
        if (less(a[i], a[i - 1]))
            return false;
    }
    return true;
}


#endif //ALGS4_SORTUTILS_H
