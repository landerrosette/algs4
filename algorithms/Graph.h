#ifndef ALGS4_GRAPH_H
#define ALGS4_GRAPH_H


#include <iostream>

#include "GraphBase.h"

namespace algs4 {
    class Graph : public GraphBase<int> {
    public:
        explicit Graph(int V) : GraphBase(V) {}
        explicit Graph(std::istream &in);

        void addEdge(int v, int w);
    };
}


#endif //ALGS4_GRAPH_H
