#ifndef ALGS4_GRAPH_H
#define ALGS4_GRAPH_H


#include "GraphBase.h"
#include <iostream>

class Graph : public GraphBase<int> {
public:
    Graph(int V) : GraphBase(V) {
    }

    Graph(std::istream &&in);

    void addEdge(int v, int w);
};


#endif //ALGS4_GRAPH_H
