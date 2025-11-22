#include "MSD.h"

#include "SortUtils.h"

void algs4::MSD::sort(std::vector<std::string> &a) {
    int N = a.size();
    internal::aux = std::vector<std::string>(N);
    internal::sort(a, 0, N - 1, 0);
}

void algs4::MSD::internal::sort(std::vector<std::string> &a, int lo, int hi, int d) {
    using namespace internal;
    if (hi <= lo + M) {
        Insertion::sort(a, lo, hi, d);
        return;
    }
    std::vector<int> count(R + 1);
    for (int i = lo; i <= hi; ++i) ++count[a[i][d] + 1];
    for (int r = 0; r < R; ++r) count[r + 1] += count[r];
    for (int i = lo; i <= hi; ++i) aux[count[a[i][d]]++] = a[i];
    for (int i = lo; i <= hi; ++i) a[i] = aux[i - lo];
    for (int r = 0; r < R; ++r)
        sort(a, lo + count[r], lo + count[r + 1] - 1, d + 1); // Recursively sort for each character value.
}

void algs4::MSD::internal::Insertion::sort(std::vector<std::string> &a, int lo, int hi, int d) {
    for (int i = lo; i <= hi; ++i) {
        for (int j = i; j > lo && internal::less(a[j], a[j - 1], d); --j)
            SortUtils::internal::exch(a, j, j - 1);
    }
}

bool algs4::MSD::internal::Insertion::internal::less(std::string_view v, std::string_view w, int d) {
    return SortUtils::internal::less(v.substr(d), w.substr(d));
}
