#include "LSD.h"

void LSD::sort(std::vector<std::string> &a, int W) {
    int N = a.size();
    int R = 256;
    std::vector<std::string> aux(N);

    for (int d = W - 1; d >= 0; --d) {
        std::vector<int> count(R + 1);
        for (int i = 0; i < N; ++i) ++count[a[i][d] + 1];         // Compute frequency counts.
        for (int r = 0; r < R; ++r) count[r + 1] += count[r];     // Transform counts to indices.
        for (int i = 0; i < N; ++i) aux[count[a[i][d]]++] = a[i]; // Distribute.
        for (int i = 0; i < N; ++i) a[i] = aux[i];                // Copy back.
    }
}
