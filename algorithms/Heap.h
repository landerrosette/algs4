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
        void sink(std::vector<T> &a, int k, int N) {
            while (2 * k <= N) {
                int j = 2 * k;
                if (j < N && less(a, j, j + 1)) ++j;
                if (!less(a, k, j)) break;
                exch(a, k, j);
                k = j;
            }
        }
    }

    template<typename T>
    void Heap::sort(std::vector<T> &a) {
        int N = a.size();
        for (int k = N / 2; k >= 1; --k)
            internal::sink(a, k, N);
        while (N > 1) {
            internal::exch(a, 1, N--);
            internal::sink(a, 1, N);
        }
    }
}


#endif //ALGS4_HEAP_H
