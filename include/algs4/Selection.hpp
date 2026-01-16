#ifndef ALGS4_SELECTION_HPP
#define ALGS4_SELECTION_HPP

#include <concepts>
#include <vector>

#include "SortUtils.hpp"

namespace algs4 {
    namespace Selection {
        template<std::totally_ordered T>
        constexpr void sort(std::vector<T> &a);
    }
}

template<std::totally_ordered T>
constexpr void algs4::Selection::sort(std::vector<T> &a) {
    using namespace SortUtils::internal;
    auto N = std::ssize(a);
    // Exchange a[i] with the smallest entry in a[i+1..N).
    for (decltype(N) i = 0; i < N; ++i) {
        auto min = i;
        for (auto j = i + 1; j < N; ++j)
            if (less(a[j], a[min]))
                min = j;
        exch(a, i, min);
    }
}

#endif // ALGS4_SELECTION_HPP
