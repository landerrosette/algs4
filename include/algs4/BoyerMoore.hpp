#ifndef ALGS4_BOYERMOORE_HPP
#define ALGS4_BOYERMOORE_HPP


#include <cstddef>
#include <string>
#include <utility>
#include <vector>

#include "SubstrSearcher.hpp"

namespace algs4 {
    class BoyerMoore : public SubstrSearcher {
    private:
        std::vector<std::ptrdiff_t> right;
        std::string pat;

    public:
        constexpr explicit BoyerMoore(std::string pat);

        constexpr std::ptrdiff_t search(std::string_view txt) const override;
    };
}

// Compute skip table.
constexpr algs4::BoyerMoore::BoyerMoore(std::string pat) : pat(std::move(pat)) {
    auto M = std::ssize(this->pat);
    int R = 256;
    right.assign(R, -1);
    for (decltype(M) j = 0; j < M; ++j) right[static_cast<unsigned char>(this->pat[j])] = j;
}

constexpr std::ptrdiff_t algs4::BoyerMoore::search(std::string_view txt) const {
    auto N = std::ssize(txt), M = std::ssize(pat);
    // Does the pattern match the text at position i?
    for (decltype(N) skip, i = 0; i <= N - M; i += skip) {
        skip = 0;
        for (auto j = M - 1; j >= 0; --j) {
            if (pat[j] != txt[i + j]) {
                skip = j - right[static_cast<unsigned char>(txt[i + j])];
                if (skip < 1) skip = 1;
                break;
            }
        }
        if (skip == 0) return i; // found
    }
    return N; // not found
}


#endif //ALGS4_BOYERMOORE_HPP
