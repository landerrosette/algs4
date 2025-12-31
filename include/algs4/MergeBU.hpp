#ifndef ALGS4_MERGEBU_HPP
#define ALGS4_MERGEBU_HPP


#include <algorithm>
#include <concepts>
#include <vector>

#include "Merge.hpp"

namespace algs4 {
    namespace MergeBU {
        template<std::totally_ordered T>
        void sort(std::vector<T> &a);
    }
}

template<std::totally_ordered T>
void algs4::MergeBU::sort(std::vector<T> &a) {
    using namespace Merge::internal;
    int N = a.size();
    aux<T> = std::vector<T>(N);
    for (int sz = 1; sz < N; sz *= 2)               // sz: subarray size
        for (int lo = 0; lo < N - sz; lo += 2 * sz) // lo: subarray index
            merge(a, lo, lo + sz - 1, std::min(lo + 2 * sz - 1, N - 1));
}


#endif //ALGS4_MERGEBU_HPP
