#ifndef STTEST_H
#define STTEST_H


#include <iostream>
#include "ST.h"

namespace STTest {
    inline constexpr char INVALID_KEY[] = "";
    inline constexpr int INVALID_VALUE = -1;

    void init(ST<std::string, int> &st, std::istream &is, std::ostream &os);

    void listAll(ST<std::string, int> &st, std::ostream &os);

    void removeSome(ST<std::string, int> &st, std::ostream &os);

    void removeAll(ST<std::string, int> &st, std::ostream &os);

    void testKeys(ST<std::string, int> &st, std::ostream &os);
}


#endif //STTEST_H
