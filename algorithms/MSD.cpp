#include "MSD.h"

bool MSD::Insertion::less(std::string_view v, std::string_view w, int d) {
    return Sorting::less(v.substr(d), w.substr(d));
}

void MSD::Insertion::sort(std::vector<std::string> &a, int lo, int hi, int d) {
    for (int i = lo; i <= hi; ++i) {
        for (int j = i; j > lo && less(a[j], a[j - 1], d); --j) {
            exch(a, j, j - 1);
        }
    }
}

void MSD::sort(std::vector<std::string> &a, int lo, int hi, int d) {
    if (hi <= lo + M) {
        Insertion::sort(a, lo, hi, d);
        return;
    }
    std::vector<int> count(R + 1);
    for (int i = lo; i <= hi; ++i) ++count[a[i][d] + 1];
    for (int r = 0; r < R; ++r) count[r + 1] += count[r];
    for (int i = lo; i <= hi; ++i) aux[count[a[i][d]]++] = a[i];
    for (int i = lo; i <= hi; ++i) a[i] = aux[i - lo];
    for (int r = 0; r < R; ++r) {
        sort(a, lo + count[r], lo + count[r + 1] - 1, d + 1); // Recursively sort for each character value.
    }
}

void MSD::sort(std::vector<std::string> &a) {
    int N = a.size();
    aux = std::vector<std::string>(N);
    sort(a, 0, N - 1, 0);
}
