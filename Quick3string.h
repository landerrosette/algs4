#ifndef QUICK3STRING_H
#define QUICK3STRING_H


#include "StringSorting.h"
#include <vector>

class Quick3string : public StringSorting {
private:
    static void sort(std::vector<std::string> &a, int lo, int hi, int d);

public:
    static void sort(std::vector<std::string> &a) { sort(a, 0, a.size() - 1, 0); }
};


#endif //QUICK3STRING_H
