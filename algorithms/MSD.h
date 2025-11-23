#ifndef ALGS4_MSD_H
#define ALGS4_MSD_H


#include <string>
#include <string_view>
#include <vector>

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


#endif //ALGS4_MSD_H
