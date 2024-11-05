#ifndef ALGS4_TESTST_H
#define ALGS4_TESTST_H


#include "ST.h"
#include "OrderedST.h"
#include <string>
#include <iostream>
#include "StringST.h"

void testST(ST<std::string, int> &&st, std::istream &&data);

void testST(OrderedST<std::string, int> &&st, std::istream &&data);

void testST(StringST<int> &&st, std::istream &&data);


#endif //ALGS4_TESTST_H
