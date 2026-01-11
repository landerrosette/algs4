#ifndef ALGS4_HEAP_HPP
#define ALGS4_HEAP_HPP


#include <concepts>
#include <cstddef>
#include <vector>

#include "SortUtils.hpp"

namespace algs4 {
    namespace Heap {
        namespace internal {
            template<std::totally_ordered T>
            bool less(const std::vector<T> &a, std::ptrdiff_t i, std::ptrdiff_t j);

            template<std::totally_ordered T>
            void exch(std::vector<T> &a, std::ptrdiff_t i, std::ptrdiff_t j);

            template<std::totally_ordered T>
            void sink(std::vector<T> &a, std::ptrdiff_t k, std::ptrdiff_t N);
        }

        template<std::totally_ordered T>
        void sort(std::vector<T> &a);
    }
}

template<std::totally_ordered T>
bool algs4::Heap::internal::less(const std::vector<T> &a, std::ptrdiff_t i, std::ptrdiff_t j) {
    return SortUtils::internal::less(a[i - 1], a[j - 1]);
}

template<std::totally_ordered T>
void algs4::Heap::internal::exch(std::vector<T> &a, std::ptrdiff_t i, std::ptrdiff_t j) {
    SortUtils::internal::exch(a[i - 1], a[j - 1]);
}

template<std::totally_ordered T>
void algs4::Heap::internal::sink(std::vector<T> &a, std::ptrdiff_t k, std::ptrdiff_t N) {
    while (2 * k <= N) {
        auto j = 2 * k;
        if (j < N && less(a, j, j + 1))
            ++j;
        if (!less(a, k, j))
            break;
        exch(a, k, j);
        k = j;
    }
}

template<std::totally_ordered T>
void algs4::Heap::sort(std::vector<T> &a) {
    using namespace internal;
    auto N = std::ssize(a);
    for (auto k = N / 2; k >= 1; --k)
        sink(a, k, N);
    while (N > 1) {
        exch(a, 1, N--);
        sink(a, 1, N);
    }
}


#endif //ALGS4_HEAP_HPP
