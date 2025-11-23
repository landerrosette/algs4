#ifndef ALGS4_QUICK3STRING_H
#define ALGS4_QUICK3STRING_H


#include <string>
#include <vector>

namespace algs4 {
    namespace Quick3string {
        namespace internal {
            void sort(std::vector<std::string> &a, int lo, int hi, int d);
        }

        inline void sort(std::vector<std::string> &a) { internal::sort(a, 0, a.size() - 1, 0); }
    }
}


#endif //ALGS4_QUICK3STRING_H
