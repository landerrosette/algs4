#ifndef ALGS4_INSERTION_HPP
#define ALGS4_INSERTION_HPP

#include <concepts>
#include <vector>

#include "SortUtils.hpp"

namespace algs4 {
    namespace Insertion {
        template<std::totally_ordered T>
        constexpr void sort(std::vector<T> &a);
    }
}

template<std::totally_ordered T>
constexpr void algs4::Insertion::sort(std::vector<T> &a) {
    using namespace SortUtils::internal;
    auto N = std::ssize(a);
    // Insert a[i] among a[i-1], a[i-2], a[i-3]...
    for (decltype(N) i = 1; i < N; ++i)
        for (auto j = i; j > 0 && less(a[j], a[j - 1]); --j)
            exch(a, j, j - 1);
}

#endif // ALGS4_INSERTION_HPP
