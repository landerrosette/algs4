#ifndef ALGS4_MERGEBU_H
#define ALGS4_MERGEBU_H


#include "Merge.h"
#include <algorithm>

class MergeBU : public Merge {
public:
    template<typename T>
    static void sort(std::vector<T> &a) {
        int N = a.size();
        std::vector<T> aux(a.size());
        for (int sz = 1; sz < N; sz *= 2) {                 // 子数组大小sz
            for (int lo = 0; lo < N - sz; lo += 2 * sz) {   // 子数组索引lo
                merge(a, aux, lo, lo + sz - 1, std::min(lo + 2 * sz - 1, N - 1));
            }
        }
    }

    // % algs4 words3.txt
    static int main();
};


#endif //ALGS4_MERGEBU_H
