#ifndef ALGS4_MERGE_H
#define ALGS4_MERGE_H


#include "SortUtils.h"

namespace algs4 {
    namespace Merge {
        template<typename T>
        void sort(std::vector<T> &a);
    }

    namespace Merge::internal {
        template<typename T>
        std::vector<T> aux;

        template<typename T>
        void merge(std::vector<T> &a, int lo, int mid, int hi) {
            int i = lo, j = mid + 1;
            for (int k = lo; k <= hi; ++k)
                aux<T>[k] = a[k];
            for (int k = lo; k <= hi; ++k) {
                if (i > mid)
                    a[k] = aux<T>[j++];
                else if (j > hi)
                    a[k] = aux<T>[i++];
                else if (SortUtils::internal::less(aux<T>[j], aux<T>[i]))
                    a[k] = aux<T>[j++];
                else
                    a[k] = aux<T>[i++];
            }
        }

        template<typename T>
        void sort(std::vector<T> &a, int lo, int hi) {
            if (hi <= lo)
                return;
            int mid = lo + (hi - lo) / 2;
            sort(a, lo, mid);
            sort(a, mid + 1, hi);
            merge(a, lo, mid, hi);
        }
    }

    template<typename T>
    void Merge::sort(std::vector<T> &a) {
        internal::aux<T> = std::vector<T>(a.size());
        internal::sort(a, 0, a.size() - 1);
    }
}


#endif //ALGS4_MERGE_H
