#ifndef ALGS4_TESTST_H
#define ALGS4_TESTST_H


#include "ST.h"
#include <string>
#include <filesystem>

void testST(ST<std::string, int> &&st, const std::filesystem::path &dataFilePath);

#endif //ALGS4_TESTST_H
