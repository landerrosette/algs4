#ifndef ALGS4_SORTING_H
#define ALGS4_SORTING_H


#include <vector>
#include <iostream>

class Sorting {
protected:
    template<typename T>
    static bool less(const T &v, const T &w) { return v < w; }

    template<typename T>
    static void exch(std::vector<T> &a, int i, int j);

public:
    template<typename T>
    static void show(const std::vector<T> &a);

    template<typename T>
    static bool isSorted(const std::vector<T> &a);
};

template<typename T>
void Sorting::exch(std::vector<T> &a, int i, int j) {
    T t = a[i];
    a[i] = a[j];
    a[j] = t;
}

template<typename T>
void Sorting::show(const std::vector<T> &a) {
    for (const auto &item: a) std::cout << item << " ";
    std::cout << "\n";
}

template<typename T>
bool Sorting::isSorted(const std::vector<T> &a) {
    for (int i = 1; i < a.size(); ++i) {
        if (less(a[i], a[i - 1])) return false;
    }
    return true;
}


#endif //ALGS4_SORTING_H
