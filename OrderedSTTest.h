#ifndef ORDEREDSTTEST_H
#define ORDEREDSTTEST_H


#include <iostream>
#include "OrderedST.h"

namespace STTest {
    void init(OrderedST<std::string, int> &st, std::istream &is, std::ostream &os);

    void removeSome(OrderedST<std::string, int> &st, std::ostream &os);

    void removeAll(OrderedST<std::string, int> &st, std::ostream &os);

    void testOrderedST(OrderedST<std::string, int> &st, std::ostream &os);
}


#endif //ORDEREDSTTEST_H
