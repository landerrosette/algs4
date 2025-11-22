#ifndef ALGS4_HEAP_H
#define ALGS4_HEAP_H


#include "SortUtils.h"

namespace algs4 {
    namespace Heap {
        template<typename T>
        void sort(std::vector<T> &a);
    }

    namespace Heap::internal {
        template<typename T>
        bool less(const std::vector<T> &a, int i, int j) { return SortUtils::internal::less(a[i - 1], a[j - 1]); }

        template<typename T>
        void exch(std::vector<T> &a, int i, int j) { SortUtils::internal::exch(a, i - 1, j - 1); }

        template<typename T>
        void sink(std::vector<T> &a, int k, int N);
    }
}

template<typename T>
void algs4::Heap::sort(std::vector<T> &a) {
    using namespace internal;
    int N = a.size();
    for (int k = N / 2; k >= 1; --k)
        sink(a, k, N);
    while (N > 1) {
        exch(a, 1, N--);
        sink(a, 1, N);
    }
}

template<typename T>
void algs4::Heap::internal::sink(std::vector<T> &a, int k, int N) {
    while (2 * k <= N) {
        int j = 2 * k;
        if (j < N && less(a, j, j + 1))
            ++j;
        if (!less(a, k, j))
            break;
        exch(a, k, j);
        k = j;
    }
}


#endif //ALGS4_HEAP_H
