#ifndef ALGS4_LSD_H
#define ALGS4_LSD_H


#include "StringSorting.h"

class LSD : public StringSorting {
public:
    static void sort(std::vector<std::string> &a, int W = 3);
};


#endif //ALGS4_LSD_H