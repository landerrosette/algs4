#ifndef ALGS4_DIGRAPH_H
#define ALGS4_DIGRAPH_H


#include "Graph.h"
#include <forward_list>
#include <iostream>

class Digraph : private Graph {
public:
    Digraph(int V) : Graph(V) {}

    Digraph(std::istream &in);

    using Graph::getV, Graph::getE;

    void addEdge(int v, int w);

    using Graph::getAdj;

    friend std::ostream &operator<<(std::ostream &os, const Digraph &G);

    Digraph reverse() const;
};


#endif //ALGS4_DIGRAPH_H
