#ifndef ALGS4_INSERTION_H
#define ALGS4_INSERTION_H


#include "Sorting.h"

class Insertion : public Sorting {
public:
    template<typename T>
    static void sort(std::vector<T> &a);
};

template<typename T>
void Insertion::sort(std::vector<T> &a) {
    int N = a.size();
    for (int i = 1; i < N; ++i) {
        // 将a[i]插入到a[i-1]、a[i-2]、a[i-3]...之中
        for (int j = i; j > 0 && less(a[j], a[j - 1]); --j) {
            exch(a, j, j - 1);
        }
    }
}


#endif //ALGS4_INSERTION_H
