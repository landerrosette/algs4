#ifndef ALGS4_TESTORDEREDST_H
#define ALGS4_TESTORDEREDST_H


#include <iostream>
#include <string>

#include "OrderedST.h"

namespace TestST {
    void init(OrderedST<std::string, int> &st, std::istream &is, std::ostream &os);

    void removeSome(OrderedST<std::string, int> &st, std::ostream &os);

    void removeAll(OrderedST<std::string, int> &st, std::ostream &os);

    void testOrderedST(const OrderedST<std::string, int> &st, std::ostream &os);
}


#endif //ALGS4_TESTORDEREDST_H
