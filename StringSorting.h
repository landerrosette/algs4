#ifndef STRINGSORTING_H
#define STRINGSORTING_H


#include "Sorting.h"
#include <string>

class StringSorting : public Sorting {
protected:
    static char charAt(const std::string &s, int d) { return d < s.length() ? s[d] : -1; }
};


#endif //STRINGSORTING_H
