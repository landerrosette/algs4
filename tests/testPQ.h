#ifndef ALGS4_TESTPQ_H
#define ALGS4_TESTPQ_H


#include "MaxPQ.h"
#include <string>
#include <filesystem>

void testPQ(MaxPQ<std::string> &&pq, const std::filesystem::path &dataFilePath);


#endif //ALGS4_TESTPQ_H
