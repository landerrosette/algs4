#include "BoyerMoore.h"

#include <utility>

// Compute skip table.
algs4::BoyerMoore::BoyerMoore(std::string pat) : pat(std::move(pat)) {
    int M = this->pat.length(), R = 256;
    right = std::vector(R, -1);
    for (int j = 0; j < M; ++j) right[this->pat[j]] = j;
}

int algs4::BoyerMoore::search(std::string_view txt) const {
    int N = txt.length(), M = pat.length();
    // Does the pattern match the text at position i?
    for (int skip, i = 0; i <= N - M; i += skip) {
        skip = 0;
        for (int j = M - 1; j >= 0; --j) {
            if (pat[j] != txt[i + j]) {
                skip = j - right[txt[i + j]];
                if (skip < 1) skip = 1;
                break;
            }
        }
        if (skip == 0) return i; // found
    }
    return N; // not found
}
