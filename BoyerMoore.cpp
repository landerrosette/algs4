#include "BoyerMoore.h"
#include <utility>

BoyerMoore::BoyerMoore(std::string pat) : pat(std::move(pat)) {
    // Compute skip table.
    int M = this->pat.length(), R = 256;
    right = std::vector(R, -1);
    for (int j = 0; j < M; ++j) right[this->pat[j]] = j;
}

int BoyerMoore::search(std::string_view txt) const {
    int N = txt.length(), M = pat.length();
    for (int skip, i = 0; i <= N - M; i += skip) {
        // Does the pattern match the text at position i?
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
