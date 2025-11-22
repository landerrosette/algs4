#ifndef ALGS4_QUICK3WAY_H
#define ALGS4_QUICK3WAY_H


#include <algorithm>
#include <random>

#include "SortUtils.h"

namespace algs4 {
    namespace Quick3way {
        template<typename T>
        void sort(std::vector<T> &a);
    }

    namespace Quick3way::internal {
        template<typename T>
        void sort(std::vector<T> &a, int lo, int hi);
    }
}

template<typename T>
void algs4::Quick3way::sort(std::vector<T> &a) {
    std::shuffle(a.begin(), a.end(), std::default_random_engine(std::random_device()()));
    internal::sort(a, 0, a.size() - 1);
}

template<typename T>
void algs4::Quick3way::internal::sort(std::vector<T> &a, int lo, int hi) {
    using namespace SortUtils::internal;
    if (lo >= hi) return;
    int lt = lo, i = lo + 1, gt = hi;
    T v = a[lo];
    while (i <= gt) {
        if (less(a[i], v)) exch(a, lt++, i++);
        else if (less(v, a[i])) exch(a, gt--, i);
        else ++i;
    } // a[lo..lt-1] < v = a[lt..gt] < a[gt+1..hi]
    sort(a, lo, lt - 1);
    sort(a, gt + 1, hi);
}


#endif //ALGS4_QUICK3WAY_H
