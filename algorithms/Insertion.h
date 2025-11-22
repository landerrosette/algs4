#ifndef ALGS4_INSERTION_H
#define ALGS4_INSERTION_H


#include "SortUtils.h"

namespace algs4 {
    namespace Insertion {
        template<typename T>
        void sort(std::vector<T> &a);
    }
}

template<typename T>
void algs4::Insertion::sort(std::vector<T> &a) {
    using namespace SortUtils::internal;
    int N = a.size();
    // Insert a[i] among a[i-1], a[i-2], a[i-3]...
    for (int i = 1; i < N; ++i) {
        for (int j = i; j > 0 && less(a[j], a[j - 1]); --j)
            exch(a, j, j - 1);
    }
}


#endif //ALGS4_INSERTION_H
