#ifndef ALGS4_QUICK_H
#define ALGS4_QUICK_H


#include <algorithm>
#include <random>

#include "SortUtils.h"

namespace algs4 {
    namespace Quick {
        template<typename T>
        void sort(std::vector<T> &a);
    }

    namespace Quick::internal {
        template<typename T>
        int partition(std::vector<T> &a, int lo, int hi);

        template<typename T>
        void sort(std::vector<T> &a, int lo, int hi);
    }
}

template<typename T>
void algs4::Quick::sort(std::vector<T> &a) {
    std::shuffle(a.begin(), a.end(), std::default_random_engine(std::random_device()()));
    internal::sort(a, 0, a.size() - 1);
}

template<typename T>
int algs4::Quick::internal::partition(std::vector<T> &a, int lo, int hi) {
    using namespace SortUtils::internal;
    int i = lo, j = hi + 1;
    T v = a[lo];
    // Scan right, scan left, check for scan complete, and exchange.
    while (true) {
        while (less(a[++i], v)) if (i == hi) break;
        while (less(v, a[--j])) if (j == lo) break;
        if (i >= j) break;
        exch(a, i, j);
    }
    exch(a, lo, j); // Put v = a[j] into position
    return j;       // with a[lo..j-1] <= a[j] <= a[j+1..hi].
}

template<typename T>
void algs4::Quick::internal::sort(std::vector<T> &a, int lo, int hi) {
    if (lo >= hi) return;
    int j = partition(a, lo, hi);
    sort(a, lo, j - 1);
    sort(a, j + 1, hi);
}


#endif //ALGS4_QUICK_H
