#ifndef ALGS4_SELECTION_H
#define ALGS4_SELECTION_H


#include "Sorting.h"

class Selection : public Sorting {
public:
    template<typename T>
    static void sort(std::vector<T> &a);
};

template<typename T>
void Selection::sort(std::vector<T> &a) {
    int N = a.size();
    for (int i = 0; i < N; ++i) {
        // Exchange a[i] with smallest entry in a[i+1..N).
        int min = i;
        for (int j = i + 1; j < N; ++j) {
            if (less(a[j], a[min])) min = j;
        }
        exch(a, i, min);
    }
}


#endif //ALGS4_SELECTION_H
