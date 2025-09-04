#ifndef ALGS4_QUICK3STRING_H
#define ALGS4_QUICK3STRING_H


#include "StringSorting.h"

class Quick3string : public StringSorting {
private:
    static void sort(std::vector<std::string> &a, int lo, int hi, int d);

public:
    static void sort(std::vector<std::string> &a) { sort(a, 0, a.size() - 1, 0); }
};


#endif //ALGS4_QUICK3STRING_H
