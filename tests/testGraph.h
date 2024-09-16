#ifndef ALGS4_TESTGRAPH_H
#define ALGS4_TESTGRAPH_H


#include "Graph.h"
#include "GraphBase.h"
#include "Digraph.h"
#include "SymbolDigraph.h"
#include "EdgeWeightedGraph.h"
#include "Paths.h"
#include "CCBase.h"
#include "DirectedDFS.h"
#include "Topological.h"
#include "MST.h"

void testPaths(const Graph &G, int s, const Paths &search);

void testCC(const GraphBase<int> &G, const CCBase &cc);

void testSearch(const Digraph &G, const DirectedDFS &reachable);

void testTopological(const SymbolDigraph &G, const Topological &top);

void testMST(const EdgeWeightedGraph &G, const MST &mst);


#endif //ALGS4_TESTGRAPH_H
