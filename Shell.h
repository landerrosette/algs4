#ifndef ALGS4_SHELL_H
#define ALGS4_SHELL_H


#include "Sorting.h"

class Shell : public Sorting {
public:
    template<typename T>
    static void sort(std::vector<T> &a);
};

template<typename T>
void Shell::sort(std::vector<T> &a) {
    int N = a.size();
    int h = 1;
    while (h < N / 3) h = h * 3 + 1;
    while (h >= 1) {
        // Insert a[i] among a[i-h], a[i-2*h], a[i-3*h]...
        for (int i = h; i < N; ++i) {
            for (int j = i; j >= h && less(a[j], a[j - h]); j -= h) {
                exch(a, j, j - h);
            }
        }
        h /= 3;
    }
}


#endif //ALGS4_SHELL_H
