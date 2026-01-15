#ifndef ALGS4_MERGE_HPP
#define ALGS4_MERGE_HPP


#include <concepts>
#include <cstddef>
#include <utility>
#include <vector>

#include "SortUtils.hpp"

namespace algs4 {
    namespace Merge {
        namespace internal {
            template<std::totally_ordered T>
            constexpr void merge(std::vector<T> &a, std::vector<T> &aux, std::ptrdiff_t lo, std::ptrdiff_t mid,
                                 std::ptrdiff_t hi);

            template<std::totally_ordered T>
            constexpr void sort(std::vector<T> &a, std::vector<T> &aux, std::ptrdiff_t lo, std::ptrdiff_t hi);
        }

        template<std::totally_ordered T>
        constexpr void sort(std::vector<T> &a);
    }
}

template<std::totally_ordered T>
constexpr void algs4::Merge::internal::merge(std::vector<T> &a, std::vector<T> &aux, std::ptrdiff_t lo,
                                             std::ptrdiff_t mid, std::ptrdiff_t hi) {
    using namespace internal;
    using namespace SortUtils::internal;
    auto i = lo, j = mid + 1;
    for (auto k = lo; k <= hi; ++k) aux[k] = std::move(a[k]);
    for (auto k = lo; k <= hi; ++k) {
        if (i > mid) a[k] = std::move(aux[j++]);
        else if (j > hi) a[k] = std::move(aux[i++]);
        else if (less(aux[j], aux[i])) a[k] = std::move(aux[j++]);
        else a[k] = std::move(aux[i++]);
    }
}

template<std::totally_ordered T>
constexpr void algs4::Merge::internal::sort(std::vector<T> &a, std::vector<T> &aux, std::ptrdiff_t lo,
                                            std::ptrdiff_t hi) {
    if (hi <= lo) return;
    auto mid = lo + (hi - lo) / 2;
    sort(a, aux, lo, mid);
    sort(a, aux, mid + 1, hi);
    merge(a, aux, lo, mid, hi);
}

template<std::totally_ordered T>
constexpr void algs4::Merge::sort(std::vector<T> &a) {
    std::vector<T> aux(std::ssize(a));
    internal::sort(a, aux, 0, std::ssize(a) - 1);
}


#endif //ALGS4_MERGE_HPP
