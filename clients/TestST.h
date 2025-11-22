#ifndef ALGS4_TESTST_H
#define ALGS4_TESTST_H


#include <iostream>
#include <string>

#include "ST.h"

namespace TestST {
    constexpr char INVALID_KEY[] = "";
    constexpr int INVALID_VALUE = -1;

    void init(algs4::ST<std::string, int> &st, std::istream &is, std::ostream &os);
    void listAll(const algs4::ST<std::string, int> &st, std::ostream &os);
    void removeSome(algs4::ST<std::string, int> &st, std::ostream &os);
    void removeAll(algs4::ST<std::string, int> &st, std::ostream &os);
    void testKeys(const algs4::ST<std::string, int> &st, std::ostream &os);
}


#endif //ALGS4_TESTST_H
