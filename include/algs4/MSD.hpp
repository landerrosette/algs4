#ifndef ALGS4_MSD_HPP
#define ALGS4_MSD_HPP


#include <string>
#include <string_view>
#include <vector>

#include "SortUtils.hpp"

namespace algs4 {
    namespace MSD {
        namespace internal {
            inline int R = 256;
            constexpr int M = 10;
            inline std::vector<std::string> aux;

            namespace Insertion {
                namespace internal {
                    bool less(std::string_view v, std::string_view w, int d);
                }

                void sort(std::vector<std::string> &a, int lo, int hi, int d);
            }

            void sort(std::vector<std::string> &a, int lo, int hi, int d);
        }

        void sort(std::vector<std::string> &a);
    }
}

inline bool algs4::MSD::internal::Insertion::internal::less(std::string_view v, std::string_view w, int d) {
    return SortUtils::internal::less(v.substr(d), w.substr(d));
}

inline void algs4::MSD::internal::Insertion::sort(std::vector<std::string> &a, int lo, int hi, int d) {
    using namespace internal;
    using namespace SortUtils::internal;
    for (int i = lo; i <= hi; ++i)
        for (int j = i; j > lo && less(a[j], a[j - 1], d); --j)
            exch(a, j, j - 1);
}

inline void algs4::MSD::internal::sort(std::vector<std::string> &a, int lo, int hi, int d) {
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

inline void algs4::MSD::sort(std::vector<std::string> &a) {
    int N = a.size();
    internal::aux = std::vector<std::string>(N);
    internal::sort(a, 0, N - 1, 0);
}


#endif //ALGS4_MSD_HPP
