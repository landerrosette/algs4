#ifndef ALGS4_DIGRAPH_H
#define ALGS4_DIGRAPH_H


#include "GraphBase.h"
#include <iostream>

class Digraph : public GraphBase<int> {
public:
    Digraph(int V) : GraphBase(V) {}

    Digraph(std::istream &&in);

    void addEdge(int v, int w);

    Digraph reverse() const;
};


#endif //ALGS4_DIGRAPH_H
