#ifndef ALGS4_MERGE_H
#define ALGS4_MERGE_H


#include "SortUtils.h"

namespace algs4 {
    namespace Merge {
        namespace internal {
            template<typename T>
            std::vector<T> aux;

            template<typename T>
            void merge(std::vector<T> &a, int lo, int mid, int hi);

            template<typename T>
            void sort(std::vector<T> &a, int lo, int hi);
        }

        template<typename T>
        void sort(std::vector<T> &a);
    }
}

template<typename T>
void algs4::Merge::internal::merge(std::vector<T> &a, int lo, int mid, int hi) {
    using namespace internal;
    using namespace SortUtils::internal;
    int i = lo, j = mid + 1;
    for (int k = lo; k <= hi; ++k) aux<T>[k] = a[k];
    for (int k = lo; k <= hi; ++k) {
        if (i > mid) a[k] = aux<T>[j++];
        else if (j > hi) a[k] = aux<T>[i++];
        else if (less(aux<T>[j], aux<T>[i])) a[k] = aux<T>[j++];
        else a[k] = aux<T>[i++];
    }
}

template<typename T>
void algs4::Merge::internal::sort(std::vector<T> &a, int lo, int hi) {
    if (hi <= lo) return;
    int mid = lo + (hi - lo) / 2;
    sort(a, lo, mid);
    sort(a, mid + 1, hi);
    merge(a, lo, mid, hi);
}

template<typename T>
void algs4::Merge::sort(std::vector<T> &a) {
    using namespace internal;
    aux<T> = std::vector<T>(a.size());
    sort(a, 0, a.size() - 1);
}


#endif //ALGS4_MERGE_H
