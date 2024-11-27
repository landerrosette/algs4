#ifndef ALGS4_GRAPH_H
#define ALGS4_GRAPH_H


#include "GraphBase.h"
#include <iostream>

class Graph : public GraphBase<int> {
public:
    explicit Graph(int V) : GraphBase(V) {}

    explicit Graph(std::istream &in);

    void addEdge(int v, int w);
};


#endif //ALGS4_GRAPH_H
