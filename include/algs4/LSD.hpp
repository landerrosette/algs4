#ifndef ALGS4_LSD_HPP
#define ALGS4_LSD_HPP

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

#include "StringSortUtils.h"

namespace algs4 {
    namespace LSD {
        constexpr void sort(std::vector<std::string> &a, std::ptrdiff_t W = 3);
    }
}

constexpr void algs4::LSD::sort(std::vector<std::string> &a, std::ptrdiff_t W) {
    using namespace StringSortUtils::internal;
    auto N = std::ssize(a);
    int R = 256;
    std::vector<std::string> aux(N);

    for (auto d = W - 1; d >= 0; --d) {
        std::vector<std::ptrdiff_t> count(R + 1);
        // Compute frequency counts.
        for (decltype(N) i = 0; i < N; ++i) ++count[charAt(a[i], d) + 1];
        // Transform counts to indices.
        for (int r = 0; r < R; ++r) count[r + 1] += count[r];
        // Distribute.
        for (decltype(N) i = 0; i < N; ++i) aux[count[charAt(a[i], d)]++] = std::move(a[i]);
        // Copy back.
        for (decltype(N) i = 0; i < N; ++i) a[i] = std::move(aux[i]);
    }
}

#endif // ALGS4_LSD_HPP
