#ifndef ALGS4_QUICK_H
#define ALGS4_QUICK_H


#include "Sorting.h"
#include <algorithm>
#include <random>

class Quick : public Sorting {
private:
    template<typename T>
    static int partition(std::vector<T> &a, int lo, int hi);

    template<typename T>
    static void sort(std::vector<T> &a, int lo, int hi);

public:
    template<typename T>
    static void sort(std::vector<T> &a);
};

template<typename T>
int Quick::partition(std::vector<T> &a, int lo, int hi) {
    int i = lo, j = hi + 1;
    T v = a[lo];
    while (true) {
        // Scan right, scan left, check for scan complete, and exchange.
        while (less(a[++i], v)) {
            if (i == hi) break;
        }
        while (less(v, a[--j])) {
            if (j == lo) break;
        }
        if (i >= j) break;
        exch(a, i, j);
    }
    exch(a, lo, j); // Put v = a[j] into position
    return j; // with a[lo..j-1] <= a[j] <= a[j+1..hi].
}

template<typename T>
void Quick::sort(std::vector<T> &a, int lo, int hi) {
    if (lo >= hi) return;
    int j = partition(a, lo, hi);
    sort(a, lo, j - 1);
    sort(a, j + 1, hi);
}

template<typename T>
void Quick::sort(std::vector<T> &a) {
    std::shuffle(a.begin(), a.end(), std::default_random_engine(std::random_device()()));
    sort(a, 0, a.size() - 1);
}


#endif //ALGS4_QUICK_H
