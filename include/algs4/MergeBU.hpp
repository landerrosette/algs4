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
    auto N = std::ssize(a);
    aux<T>.resize(N);
    for (decltype(N) sz = 1; sz < N; sz = sz + sz)           // sz: subarray size
        for (decltype(N) lo = 0; lo < N - sz; lo += sz + sz) // lo: subarray index
            merge(a, lo, lo + sz - 1, std::min(lo + sz + sz - 1, N - 1));
}


#endif //ALGS4_MERGEBU_HPP
