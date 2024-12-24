#ifndef ALGS4_HEAP_H
#define ALGS4_HEAP_H


#include "Sorting.h"

class Heap : public Sorting {
private:
    template<typename T>
    static void sink(std::vector<T> &a, int k, int N);

    template<typename T>
    static bool less(const std::vector<T> &a, int i, int j) { return a[i - 1] < a[j - 1]; }

    template<typename T>
    static void exch(std::vector<T> &a, int i, int j) { std::swap(a[i - 1], a[j - 1]); }

public:
    template<typename T>
    static void sort(std::vector<T> &a);
};

template<typename T>
void Heap::sink(std::vector<T> &a, int k, int N) {
    while (2 * k <= N) {
        int j = 2 * k;
        if (j < N && less(a, j, j + 1)) ++j;
        if (!less(a, k, j)) break;
        exch(a, k, j);
        k = j;
    }
}

template<typename T>
void Heap::sort(std::vector<T> &a) {
    int N = a.size();
    for (int k = N / 2; k >= 1; --k) sink(a, k, N);
    while (N > 1) {
        exch(a, 1, N--);
        sink(a, 1, N);
    }
}


#endif //ALGS4_HEAP_H
