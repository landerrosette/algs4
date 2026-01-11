#ifndef ALGS4_SHELL_HPP
#define ALGS4_SHELL_HPP


#include <concepts>
#include <vector>

#include "SortUtils.hpp"

namespace algs4 {
    namespace Shell {
        template<std::totally_ordered T>
        void sort(std::vector<T> &a);
    }
}

template<std::totally_ordered T>
void algs4::Shell::sort(std::vector<T> &a) {
    using namespace SortUtils::internal;
    auto N = std::ssize(a);
    decltype(N) h = 1;
    while (h < N / 3) h = h * 3 + 1;
    while (h >= 1) {
        // Insert a[i] among a[i-h], a[i-2*h], a[i-3*h]...
        for (auto i = h; i < N; ++i)
            for (auto j = i; j >= h && less(a[j], a[j - h]); j -= h)
                exch(a, j, j - h);
        h /= 3;
    }
}


#endif //ALGS4_SHELL_HPP
