#ifndef ALGS4_SELECTION_H
#define ALGS4_SELECTION_H


#include <concepts>

#include "SortUtils.h"

namespace algs4 {
    namespace Selection {
        template<std::totally_ordered T>
        void sort(std::vector<T> &a);
    }
}

template<std::totally_ordered T>
void algs4::Selection::sort(std::vector<T> &a) {
    using namespace SortUtils::internal;
    int N = a.size();
    // Exchange a[i] with the smallest entry in a[i+1..N).
    for (int i = 0; i < N; ++i) {
        int min = i;
        for (int j = i + 1; j < N; ++j)
            if (less(a[j], a[min]))
                min = j;
        exch(a, i, min);
    }
}


#endif //ALGS4_SELECTION_H
