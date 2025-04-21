#ifndef ALGS4_MERGE_H
#define ALGS4_MERGE_H


#include "Sorting.h"

class Merge : public Sorting {
private:
    template<typename T>
    static void sort(std::vector<T> &a, int lo, int hi);

protected:
    template<typename T>
    inline static std::vector<T> aux;

    template<typename T>
    static void merge(std::vector<T> &a, int lo, int mid, int hi);

public:
    template<typename T>
    static void sort(std::vector<T> &a);
};

template<typename T>
void Merge::sort(std::vector<T> &a, int lo, int hi) {
    if (hi <= lo) return;
    int mid = lo + (hi - lo) / 2;
    sort(a, lo, mid);
    sort(a, mid + 1, hi);
    merge(a, lo, mid, hi);
}

template<typename T>
void Merge::merge(std::vector<T> &a, int lo, int mid, int hi) {
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
void Merge::sort(std::vector<T> &a) {
    aux<T> = std::vector<T>(a.size());
    sort(a, 0, a.size() - 1);
}


#endif //ALGS4_MERGE_H
