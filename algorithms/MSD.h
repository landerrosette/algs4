#ifndef ALGS4_MSD_H
#define ALGS4_MSD_H


#include <string>
#include <string_view>
#include <vector>

namespace algs4 {
    namespace MSD {
        void sort(std::vector<std::string> &a);
    }

    namespace MSD::internal {
        inline int R = 256;
        constexpr int M = 10;
        inline std::vector<std::string> aux;

        void sort(std::vector<std::string> &a, int lo, int hi, int d);

        namespace Insertion {
            void sort(std::vector<std::string> &a, int lo, int hi, int d);
        }

        namespace Insertion::internal {
            bool less(std::string_view v, std::string_view w, int d);
        }
    }
}


#endif //ALGS4_MSD_H
