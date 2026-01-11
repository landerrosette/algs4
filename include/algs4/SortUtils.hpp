#ifndef ALGS4_SORTUTILS_HPP
#define ALGS4_SORTUTILS_HPP


#include <concepts>
#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

namespace algs4 {
    namespace SortUtils {
        namespace internal {
            template<std::totally_ordered T>
            bool less(const T &v, const T &w) { return v < w; }

            template<std::totally_ordered T>
            void exch(std::vector<T> &a, std::integral auto i, std::integral auto j);
        }

        template<std::totally_ordered T>
        void show(const std::vector<T> &a);

        template<std::totally_ordered T>
        bool isSorted(const std::vector<T> &a);
    }
}

template<std::totally_ordered T>
void algs4::SortUtils::internal::exch(std::vector<T> &a, std::integral auto i, std::integral auto j) {
    using std::swap;
    swap(a[i], a[j]);
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
    for (std::ptrdiff_t i = 1; i < std::ssize(a); ++i)
        if (less(a[i], a[i - 1])) return false;
    return true;
}


#endif //ALGS4_SORTUTILS_HPP
