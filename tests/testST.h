#ifndef ALGS4_TESTST_H
#define ALGS4_TESTST_H


#include "ST.h"
#include "OrderedST.h"
#include <string>
#include <filesystem>

void testBasicST(ST<std::string, int> &&st, const std::filesystem::path &dataFilePath);

void testOrderedST(OrderedST<std::string, int> &&st, const std::filesystem::path &dataFilePath);


#endif //ALGS4_TESTST_H
