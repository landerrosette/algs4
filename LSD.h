#ifndef LSD_H
#define LSD_H


#include <vector>
#include <string>
#include "Sorting.h"

class LSD : public Sorting {
public:
    static void sort(std::vector<std::string> &a, int W = 3);
};


#endif //LSD_H
