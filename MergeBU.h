#ifndef ALGS4_MERGEBU_H
#define ALGS4_MERGEBU_H


#include <algorithm>

#include "Merge.h"

class MergeBU : public Merge {
public:
    template<typename T>
    static void sort(std::vector<T> &a);
};

template<typename T>
void MergeBU::sort(std::vector<T> &a) {
    int N = a.size();
    aux<T> = std::vector<T>(N);
    // sz: subarray size
    for (int sz = 1; sz < N; sz *= 2) {
        // lo: subarray index
        for (int lo = 0; lo < N - sz; lo += 2 * sz) {
            merge(a, lo, lo + sz - 1, std::min(lo + 2 * sz - 1, N - 1));
        }
    }
}


#endif //ALGS4_MERGEBU_H
