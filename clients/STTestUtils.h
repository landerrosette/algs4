#ifndef ALGS4_STTESTUTILS_H
#define ALGS4_STTESTUTILS_H


#include <iostream>
#include <string>

#include "algs4/ST.h"

namespace STTestUtils {
    constexpr char INVALID_KEY[] = "null";
    constexpr int INVALID_VALUE = -1;

    void init(algs4::ST<std::string, int> &st, std::istream &is, std::ostream &os);
    void listAll(const algs4::ST<std::string, int> &st, std::ostream &os);
    void removeSome(algs4::ST<std::string, int> &st, std::ostream &os);
    void removeAll(algs4::ST<std::string, int> &st, std::ostream &os);
    void testKeys(const algs4::ST<std::string, int> &st, std::ostream &os);
}


#endif //ALGS4_STTESTUTILS_H
