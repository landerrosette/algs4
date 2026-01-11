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
        std::string pat;
        std::vector<std::vector<std::ptrdiff_t> > dfa;

    public:
        explicit KMP(std::string pat);

        std::ptrdiff_t search(std::string_view txt) const override;
    };
}

// Build DFA from pattern.
inline algs4::KMP::KMP(std::string pat) : pat(std::move(pat)) {
    auto M = std::ssize(this->pat);
    int R = 256;
    dfa.assign(R, std::vector<std::ptrdiff_t>(M));
    dfa[static_cast<unsigned char>(this->pat[0])][0] = 1;
    // Compute dfa[][j].
    for (decltype(M) X = 0, j = 1; j < M; ++j) {
        for (int c = 0; c < R; ++c) dfa[c][j] = dfa[c][X];        // Copy mismatch cases.
        dfa[static_cast<unsigned char>(this->pat[j])][j] = j + 1; // Set match case.
        X = dfa[static_cast<unsigned char>(this->pat[j])][X];     // Update restart state.
    }
}

inline std::ptrdiff_t algs4::KMP::search(std::string_view txt) const {
    auto N = std::ssize(txt), M = std::ssize(pat);
    decltype(N) i, j;
    for (i = 0, j = 0; i < N && j < M; ++i) j = dfa[static_cast<unsigned char>(txt[i])][j];
    if (j == M) return i - M; // found (hit end of pattern)
    else return N;            // not found (hit end of text)
}


#endif //ALGS4_KMP_HPP
