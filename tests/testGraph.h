#ifndef ALGS4_TESTGRAPH_H
#define ALGS4_TESTGRAPH_H


#include "Graph.h"
#include "Paths.h"
#include "CC.h"

void testPaths(const Graph &G, Paths &&search, int s);

void testCC(const Graph &G, CC &&cc);

#endif //ALGS4_TESTGRAPH_H
