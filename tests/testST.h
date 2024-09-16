#ifndef ALGS4_TESTST_H
#define ALGS4_TESTST_H


#include "ST.h"
#include "OrderedST.h"
#include <string>
#include <iostream>

void testBasicST(ST<std::string, int> &&st, std::istream &&data);

void testOrderedST(OrderedST<std::string, int> &&st, std::istream &&data);


#endif //ALGS4_TESTST_H
