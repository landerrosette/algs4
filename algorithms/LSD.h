#ifndef LSD_H
#define LSD_H


#include "StringSorting.h"

class LSD : public StringSorting {
public:
    static void sort(std::vector<std::string> &a, int W = 3);
};


#endif //LSD_H
