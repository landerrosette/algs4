#ifndef ALGS4_QUICK3STRING_H
#define ALGS4_QUICK3STRING_H


#include <string>
#include <vector>

namespace algs4 {
    namespace Quick3string {
        void sort(std::vector<std::string> &a);
    }

    namespace Quick3string::internal {
        void sort(std::vector<std::string> &a, int lo, int hi, int d);
    }
}


#endif //ALGS4_QUICK3STRING_H
