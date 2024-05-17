#ifndef ALGS4_MERGE_H
#define ALGS4_MERGE_H


#include "Sorting.h"

class Merge : public Sorting {
protected:
    template<typename T>
    static void merge(std::vector<T> &a, std::vector<T> &aux, int lo, int mid, int hi) {
        int i = lo, j = mid + 1;
        for (int k = lo; k <= hi; ++k) aux[k] = a[k];
        for (int k = lo; k <= hi; ++k) {
            if (i > mid) {
                a[k] = aux[j++];
            } else if (j > hi) {
                a[k] = aux[i++];
            } else if (less(aux[j], aux[i])) {
                a[k] = aux[j++];
            } else {
                a[k] = aux[i++];
            }
        }
    }

private:
    template<typename T>
    static void sort(std::vector<T> &a, std::vector<T> &aux, int lo, int hi) {
        if (lo >= hi) return;
        int mid = (lo + hi) / 2;
        sort(a, aux, lo, mid);
        sort(a, aux, mid + 1, hi);
        merge(a, aux, lo, mid, hi);
    }

public:
    template<typename T>
    static void sort(std::vector<T> &a) {
        std::vector<T> aux(a.size());
        sort(a, aux, 0, a.size() - 1);
    }
};


#endif //ALGS4_MERGE_H
