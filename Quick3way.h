#ifndef ALGS4_QUICK3WAY_H
#define ALGS4_QUICK3WAY_H


#include "Sorting.h"
#include <algorithm>
#include <random>

class Quick3way : public Sorting {
private:
    template<typename T>
    static void sort(std::vector<T> &a, int lo, int hi) {
        if (lo >= hi) return;
        int lt = lo, i = lo + 1, gt = hi;
        T v = a[lo];
        while (i <= gt) {
            if (a[i] < v) exch(a, lt++, i++);
            else if (a[i] > v) exch(a, gt--, i);
            else i++;
        }   // 现在 a[lo..lt-1] < v = a[lt..gt] < a[gt+1..hi]成立
        sort(a, lo, lt - 1);
        sort(a, gt + 1, hi);
    }

public:
    template<typename T>
    static void sort(std::vector<T> &a) {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(a.begin(), a.end(), g);
        sort(a, 0, a.size() - 1);
    }

    // % algs4 words3.txt
    static void main();
};


#endif //ALGS4_QUICK3WAY_H
