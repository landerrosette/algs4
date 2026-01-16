#ifndef ALGS4_KMP_HPP
#define ALGS4_KMP_HPP

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

#include "SubstrSearcher.hpp"

namespace algs4 {
    class KMP : public SubstrSearcher {
    private:
        std::string pat_;
        std::vector<std::vector<std::ptrdiff_t> > dfa_;

    public:
        constexpr explicit KMP(std::string pat);

        constexpr std::ptrdiff_t search(std::string_view txt) const override;
    };
}

// Build DFA from pattern.
constexpr algs4::KMP::KMP(std::string pat) : pat_(std::move(pat)) {
    auto M = std::ssize(pat_);
    int R = 256;
    dfa_.assign(R, std::vector<std::ptrdiff_t>(M));
    dfa_[static_cast<unsigned char>(pat_[0])][0] = 1;
    // Compute dfa_[][j].
    for (decltype(M) X = 0, j = 1; j < M; ++j) {
        for (int c = 0; c < R; ++c) dfa_[c][j] = dfa_[c][X];  // Copy mismatch cases.
        dfa_[static_cast<unsigned char>(pat_[j])][j] = j + 1; // Set match case.
        X = dfa_[static_cast<unsigned char>(pat_[j])][X];     // Update restart state.
    }
}

constexpr std::ptrdiff_t algs4::KMP::search(std::string_view txt) const {
    auto N = std::ssize(txt), M = std::ssize(pat_);
    decltype(N) i, j;
    for (i = 0, j = 0; i < N && j < M; ++i) j = dfa_[static_cast<unsigned char>(txt[i])][j];
    if (j == M) return i - M; // found (hit end of pattern)
    else return N;            // not found (hit end of text)
}

#endif // ALGS4_KMP_HPP
