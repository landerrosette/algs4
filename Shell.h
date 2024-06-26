#ifndef ALGS4_SHELL_H
#define ALGS4_SHELL_H


#include "Sorting.h"

class Shell : public Sorting {
public:
    template<typename T>
    static void sort(std::vector<T> &a) {
        int N = a.size();
        int h = 1;
        while (h < N / 3) h = h * 3 + 1;
        while (h >= 1) {
            for (int i = h; i < N; ++i) {
                // 将a[i]插入到a[i-h]、a[i-2h]、a[i-3h]...之中
                for (int j = i; j >= h && less(a[j], a[j - h]); j -= h) {
                    exch(a, j, j - h);
                }
            }
            h /= 3;
        }
    }

    // % algs4 words3.txt
    static void main();
};


#endif //ALGS4_SHELL_H
