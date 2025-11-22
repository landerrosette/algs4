#ifndef ALGS4_DIGRAPH_H
#define ALGS4_DIGRAPH_H


#include <iostream>

#include "GraphBase.h"

namespace algs4 {
    class Digraph : public GraphBase<int> {
    public:
        explicit Digraph(int V) : GraphBase(V) {}
        explicit Digraph(std::istream &in);

        void addEdge(int v, int w);
        Digraph reverse() const;
    };
}


#endif //ALGS4_DIGRAPH_H
