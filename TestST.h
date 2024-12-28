#ifndef TESTST_H
#define TESTST_H


#include <iostream>
#include <string>
#include "ST.h"

namespace TestST {
    inline constexpr char INVALID_KEY[] = "";
    inline constexpr int INVALID_VALUE = -1;

    void init(ST<std::string, int> &st, std::istream &is, std::ostream &os);

    void listAll(const ST<std::string, int> &st, std::ostream &os);

    void removeSome(ST<std::string, int> &st, std::ostream &os);

    void removeAll(ST<std::string, int> &st, std::ostream &os);

    void testKeys(const ST<std::string, int> &st, std::ostream &os);
}


#endif //TESTST_H
