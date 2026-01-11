#ifndef ALGS4_ORDEREDSTTESTUTILS_HPP
#define ALGS4_ORDEREDSTTESTUTILS_HPP


#include <iosfwd>
#include <string>

#include "algs4/OrderedST.hpp"

namespace STTestUtils {
    void init(algs4::OrderedST<std::string, int> &st, std::istream &is, std::ostream &os);
    void removeSome(algs4::OrderedST<std::string, int> &st, std::ostream &os);
    void removeAll(algs4::OrderedST<std::string, int> &st, std::ostream &os);
    void testOrderedST(const algs4::OrderedST<std::string, int> &st, std::ostream &os);
}


#endif //ALGS4_ORDEREDSTTESTUTILS_HPP
