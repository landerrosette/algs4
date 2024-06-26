#ifndef ALGS4_QUICK_H
#define ALGS4_QUICK_H


#include "Sorting.h"
#include <algorithm>
#include <random>

class Quick : public Sorting {
private:
    template<typename T>
    static int partition(std::vector<T> &a, int lo, int hi) {
        int i = lo, j = hi + 1;
        T v = a[lo];
        while (true) {
            // 扫描左右，检查扫描是否结束并交换元素
            while (less(a[++i], v)) {
                if (i == hi) break;
            }
            while (less(v, a[--j])) {
                if (j == lo) break;
            }
            if (i >= j) break;
            exch(a, i, j);
        }
        exch(a, lo, j);
        return j;   // a[lo..j-1] <= a[j] <= a[j+1..hi] 达成
    }

    template<typename T>
    static void sort(std::vector<T> &a, int lo, int hi) {
        if (lo >= hi) return;
        int j = partition(a, lo, hi);
        sort(a, lo, j - 1);
        sort(a, j + 1, hi);
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
    static int main();
};


#endif //ALGS4_QUICK_H
