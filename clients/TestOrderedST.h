#ifndef ALGS4_TESTORDEREDST_H
#define ALGS4_TESTORDEREDST_H


#include <iostream>
#include <string>

#include "OrderedST.h"

namespace TestST {
    void init(algs4::OrderedST<std::string, int> &st, std::istream &is, std::ostream &os);
    void removeSome(algs4::OrderedST<std::string, int> &st, std::ostream &os);
    void removeAll(algs4::OrderedST<std::string, int> &st, std::ostream &os);
    void testOrderedST(const algs4::OrderedST<std::string, int> &st, std::ostream &os);
}


#endif //ALGS4_TESTORDEREDST_H
