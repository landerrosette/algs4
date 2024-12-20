#include "KMP.h"
#include <utility>

KMP::KMP(std::string pat) : pat(std::move(pat)) {
    // Build DFA from pattern.
    int M = this->pat.length(), R = 256;
    dfa = std::vector(R, std::vector<int>(M));
    dfa[this->pat[0]][0] = 1;
    for (int X = 0, j = 1; j < M; ++j) {
        // Compute dfa[][j].
        for (int c = 0; c < R; ++c) dfa[c][j] = dfa[c][X]; // Copy mismatch cases.
        dfa[this->pat[j]][j] = j + 1;                      // Set match case.
        X = dfa[this->pat[j]][X];                          // Update restart state.
    }
}

int KMP::search(std::string_view txt) const {
    int i, j, N = txt.length(), M = pat.length();
    for (i = 0, j = 0; i < N && j < M; ++i) j = dfa[txt[i]][j];
    if (j == M) return i - M; // found (hit end of pattern)
    else return N;            // not found (hit end of text)
}
